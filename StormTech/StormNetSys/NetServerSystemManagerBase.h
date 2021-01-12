#pragma once

#include "StormNet/NetSerialize.h"
#include "StormNet/NetDeserialize.h"

#include "StormNetSys/NetHistoryList.h"
#include "StormNetSys/NetCircularBuffer.h"
#include "StormNetSys/NetSyncList.h"
#include "StormNetSys/NetStateChangedSyncList.h"
#include "StormNetSys/NetCOWPtr.h"
#include "StormNetSys/NetTypeIndex.h"


template <std::size_t Index>
struct NetServerSystemIndex
{
  static constexpr std::size_t SystemIndex = Index;
};

template <typename ... BaseSystems>
class NetServerSystemManagerBase
{
protected:

  template <typename T>
  static constexpr std::size_t GetSystemIndex()
  {
    return NetTypeIndex<T, std::tuple<BaseSystems...>>::value;
  }

  template <typename System, typename State, typename ClientLocalData>
  void InitSystem(System & system, NetCOWPtr<State> * state, NetCOWPtr<ClientLocalData> * client_local, bool authority)
  {
    system.m_IsAuthority = authority;
    system.m_State = state;
    system.m_ClientLocalData = client_local;
  }

  template <typename Element, typename NetBitWriter>
  void SerializeElement(const Element & elem, NetBitWriter & writer)
  {
    NetSerializer<Element, NetBitWriter> serializer;
    serializer(elem, writer);
  }

  template <typename Element, typename NetBitReader>
  void DeserializeElement(Element & elem, NetBitReader & reader)
  {
    NetDeserializer<Element, NetBitReader> deserializer;
    deserializer(elem, reader);
  }

  template <typename Element, typename TimeValue, typename NetBitWriter>
  void SerializeHistoryList(const NetHistoryList<Element, TimeValue> & list, TimeValue since_frame,
      TimeValue base_frame, TimeValue max_history, int max_elements, NetBitWriter & writer)
  {
    auto cursor = writer.Reserve(GetRequiredBits(max_elements));

    int num_elements = 0;
    list.VisitElementsSince(since_frame, [&](TimeValue frame, const Element & element)
    {
      TimeValue t = frame - base_frame;
      writer.WriteBtis(t, GetRequiredBits(max_history));

      SerializeElement(element, writer);

      ++num_elements;
    });

    cursor.WriteBits(num_elements, GetRequiredBits(max_elements));
  }

  template <typename Element, typename TimeValue, typename NetBitWriter, typename Filter>
  void SerializeHistoryListWithFilter(const NetHistoryList<Element, TimeValue> & list, TimeValue since_frame,
      TimeValue base_frame, TimeValue max_history, int max_elements, NetBitWriter & writer, Filter && filter)
  {
    auto cursor = writer.Reserve(GetRequiredBits(max_elements));

    int num_elements = 0;
    list.VisitElementsSince(since_frame, [&](TimeValue frame, const Element & element)
    {
      if(filter(frame, element))
      {
        TimeValue t = frame - base_frame;
        writer.WriteBtis(t, GetRequiredBits(max_history));

        SerializeElement(element, writer);

        ++num_elements;
      }
    });

    cursor.WriteBits(num_elements, GetRequiredBits(max_elements));
  }

  template <typename Element, typename TimeValue, typename NetBitReader, typename Processor>
  void DeserializeHistoryList(TimeValue base_frame, TimeValue max_history, int max_elements, NetBitReader & reader, Processor && processor)
  {
    int num_elements = static_cast<int>(reader.ReadUBits(GetRequiredBits(max_elements)));
    for(int elem_index = 0; elem_index < num_elements; ++elem_index)
    {
      TimeValue t = reader.ReadUBits(GetRequiredBits(max_elements));

      Element element;
      DeserializeElement(element, reader);

      processor(t, std::move(element));
    }
  }

  template <typename Element, int MaxHistory, typename NetBitWriter>
  void SerializeCircularBuffer(const NetCircularBuffer<NetCOWPtr<Element>, MaxHistory> & list, int history_index, NetBitWriter & writer)
  {
    assert(history_index < MaxHistory);

    auto cursor = writer.Reserve(GetRequiredBits(MaxHistory));

    auto work_element = list.Get(history_index);
    --history_index;

    int num_elements = 0;

    while(history_index >= 0)
    {
      auto next_element = list.Get(history_index);
      if(work_element != next_element)
      {
        writer.WriteBits(history_index, GetRequiredBits(MaxHistory));
        SerializeElement(work_element, writer);

        num_elements++;
      }

      work_element = next_element;
      --history_index;
    }

    cursor.WriteBits(num_elements, GetRequiredBits(MaxHistory));
  }

  template <typename Element, int MaxHistory, typename NetBitReader>
  void DeserializeCircularBuffer(NetCircularBuffer<NetCOWPtr<Element>, MaxHistory> & list, int base_history_index,
      NetBitReader & reader, int current_frame, std::vector<std::pair<int, NetCOWPtr<Element>>> & future_elements)
  {
    NetCOWPtr<Element> element;
    int last_history_index = MaxHistory;

    int num_elements = static_cast<int>(reader.ReadUBits(GetRequiredBits(MaxHistory)));
    for(int elem_index = 0; elem_index < num_elements; ++elem_index)
    {
      int history_index = static_cast<int>(reader.ReadUBits(GetRequiredBits(MaxHistory))) + base_history_index;
      element.Emplace();

      DeserializeElement(element.GetForModify(), reader);

      if(history_index < 0)
      {
        future_elements.push_back(std::make_pair(current_frame - history_index, std::move(element)));
      }
      else if(history_index < MaxHistory)
      {
        while(last_history_index > history_index)
        {
          list.SetAt(element, last_history_index);
          --last_history_index;
        }
      }
    }

    if(element)
    {
      while(last_history_index >= 0)
      {
        list.SetAt(element, last_history_index);
        --last_history_index;
      }
    }
  }

  template <std::size_t SegmentBits, std::size_t FrameOffsetBits, typename T, typename Serializer>
  void SerializeSyncList(const NetSyncList<T> & list, int current_frame, NetBitWriter & writer, Serializer && serializer) const
  {
    if constexpr (!std::is_void_v<T>)
    {
      auto cursor = writer.Reserve(SegmentBits);
      int num_elements = 0;

      int max_elements = (1U << SegmentBits) - 1;
      int max_frame_offset = (1U << FrameOffsetBits) - 1;

      list.VisitElements([&](int frame, const T & element)
      {
        if (current_frame < frame || current_frame - frame > max_frame_offset)
        {
          return;
        }

        writer.WriteBits(current_frame - frame, FrameOffsetBits);
        serializer(element, writer);

        num_elements++;

        if (num_elements >= max_elements)
        {
          cursor.WriteBits(max_elements, SegmentBits);
          num_elements = 0;
          cursor = writer.Reserve(SegmentBits);
        }
      });

      cursor.WriteBits(num_elements, SegmentBits);
    }
  }

  template <std::size_t SegmentBits, std::size_t FrameOffsetBits, std::size_t MaxClients, typename T, typename Serializer>
  void SerializeMultiSyncList(const NetMultiSyncList<T, MaxClients> & list, std::size_t client_index, int current_frame, NetBitWriter & writer, Serializer && serializer) const
  {
    if constexpr (!std::is_void_v<T>)
    {
      auto cursor = writer.Reserve(SegmentBits);
      int num_elements = 0;

      int max_elements = (1U << SegmentBits) - 1;
      int max_frame_offset = (1U << FrameOffsetBits) - 1;

      list.VisitElementsForClient(client_index, [&](int frame, const T & element)
      {
        if (current_frame < frame || current_frame - frame > max_frame_offset)
        {
          return;
        }

        writer.WriteBits(current_frame - frame, FrameOffsetBits);
        serializer(element, writer);

        num_elements++;

        if (num_elements >= max_elements)
        {
          cursor.WriteBits(max_elements, SegmentBits);
          num_elements = 0;
          cursor = writer.Reserve(SegmentBits);
        }
      });

      cursor.WriteBits(num_elements, SegmentBits);
    }
  }

  template <std::size_t SegmentBits, std::size_t FrameOffsetBits, typename T, typename Deserializer, typename Visitor>
  void DeserializeSyncList(int current_frame, int last_sync_frame, NetBitReader & reader, Deserializer && deserializer, Visitor && visitor)
  {
    if constexpr (!std::is_void_v<T>)
    {
      while (true)
      {
        int num_elements = static_cast<int>(reader.ReadUBits(SegmentBits));
        for (int index = 0; index < num_elements; ++index)
        {
          int frames_past = static_cast<int>(reader.ReadUBits(FrameOffsetBits));
          int frame = current_frame - frames_past;

          T t;
          deserializer(t, reader);

          if(frame > last_sync_frame)
          {
            visitor(frame, std::move(t));
          }
        }

        if (num_elements != (1U << FrameOffsetBits))
        {
          break;
        }
      }
    }
  }

  template <bool SyncOnlyIfChanged, typename T, typename Serializer>
  void SerializeStateChangeSyncList(const NetCOWPtr<T> & state, bool force,
      const NetStateChangedSyncList<SyncOnlyIfChanged, T> & list, NetBitWriter & writer, Serializer && serializer) const
  {
    if constexpr (!std::is_void_v<T>)
    {
      if(list.AnyChanged() || force)
      {
        writer.WriteBits(1, 1);
        serializer(state.Get(), writer);
      }
      else
      {
        writer.WriteBits(0, 1);
      }
    }
  }

  template <bool SyncOnlyIfChanged, std::size_t MaxClients, typename T, typename Serializer>
  void SerializeMultiStateChangeSyncList(const NetCOWPtr<T> & state, bool force,
      const NetStateChangedMultiSyncList<SyncOnlyIfChanged, MaxClients, T> & list,
      std::size_t client_index, NetBitWriter & writer, Serializer && serializer) const
  {
    if constexpr (!std::is_void_v<T>)
    {
      if(list.AnyChanged(client_index) || force)
      {
        writer.WriteBits(1, 1);
        serializer(state.Get(), writer);
      }
      else
      {
        writer.WriteBits(0, 1);
      }
    }
  }

  template <bool SyncOnlyIfChanged, typename T, typename Deserializer>
  void DeserializeStateChangeSyncList(NetCOWPtr<T> & state, NetCOWPtr<T> & last_synced_state, NetBitReader & reader, Deserializer && deserializer)
  {
    if constexpr (!std::is_void_v<T>)
    {
      if(reader.ReadUBits(1))
      {
        deserializer(state.GetForModify(), reader);
        last_synced_state = state;
      }
      else
      {
        state = last_synced_state;
      }
    }
  }

  template <typename Visitor>
  void VisitSystems(std::tuple<BaseSystems...> & systems, Visitor && visitor)
  {
    VisitSystemsInternal<0, Visitor>(systems, std::forward<Visitor>(visitor));
  }

  template <typename Visitor>
  void VisitSystems(const std::tuple<BaseSystems...> & systems, Visitor && visitor) const
  {
    VisitSystemsInternal<0, Visitor>(systems, std::forward<Visitor>(visitor));
  }

private:
  template <std::size_t Index, typename Visitor>
  void VisitSystemsInternal(std::tuple<BaseSystems...> & systems, Visitor && visitor)
  {
    if constexpr (Index < sizeof...(BaseSystems))
    {
      auto & system = std::get<Index>(systems);
      visitor(system, NetServerSystemIndex<Index>{});
      VisitSystemsInternal<Index + 1, Visitor>(systems, std::forward<Visitor>(visitor));
    }
  }

  template <std::size_t Index, typename Visitor>
  void VisitSystemsInternal(const std::tuple<BaseSystems...> & systems, Visitor && visitor) const
  {
    if constexpr (Index < sizeof...(BaseSystems))
    {
      auto & system = std::get<Index>(systems);
      visitor(system, NetServerSystemIndex<Index>{});
      VisitSystemsInternal<Index + 1, Visitor>(systems, std::forward<Visitor>(visitor));
    }
  }
};

