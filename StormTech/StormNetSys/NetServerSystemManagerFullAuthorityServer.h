
#pragma once

#include "StormNetSys/NetServerSystemManagerBase.h"
#include "StormNetSys/NetSyncList.h"

template <std::size_t MaxClients, typename ... Systems>
class NetServerSystemManagerFullAuthorityServer : public NetServerSystemManagerBase<Systems...>
{
public:
  
  template <typename ... SystemInit>
  explicit NetServerSystemManagerFullAuthorityServer(SystemInit && ... system_init) :
    m_Systems(std::forward<SystemInit>(system_init)...)
  {
    static_assert(sizeof...(Systems) == sizeof...(SystemInit), "You must provide system init info for all systems");
    this->VisitSystems(m_Systems, [&](auto & system, auto index_type)
    {
      constexpr std::size_t Index = std::decay_t<decltype(index_type)>::SystemIndex;
      auto & state = std::get<Index>(m_State);

      state = system.CreateInitialState();

      auto & client_local = std::get<Index>(m_ClientLocalData);
      this->InitSystem(system, &state, &client_local[0], true);
    });
  }

  void AddClient(std::size_t client_index)
  {
    m_ConnectedClients.set(client_index);
    m_ForceSync.set(client_index);
    m_LastClientFrame[client_index] = 0;

    this->VisitSystems(m_Systems, [&](auto & system, auto index_type)
    {
      constexpr std::size_t Index = std::decay_t<decltype(index_type)>::SystemIndex;
      using SystemType = std::decay_t<decltype(system)>;

      if(!std::is_void_v<typename SystemType::ClientLocalDataType>)
      {
        auto & client_local_data = std::get<Index>(m_ClientLocalData)[client_index];
        client_local_data.Emplace();
      }

      system.AddClient(client_index);
    });
  }

  void RemoveClient(std::size_t client_index)
  {
    m_ConnectedClients.reset(client_index);

    this->VisitSystems(m_Systems, [&](auto & system, auto index_type)
    {
      system.RemoveClient(client_index);

      constexpr std::size_t Index = std::decay_t<decltype(index_type)>::SystemIndex;
      using SystemType = std::decay_t<decltype(system)>;

      if constexpr (!std::is_void_v<typename SystemType::StateType>)
      {
        auto & state_changed_list = std::get<Index>(m_StateSyncList);
        state_changed_list.RemoveClient(client_index);
      }

      if constexpr (!std::is_void_v<typename SystemType::ClientLocalDataType>)
      {
        auto & client_local_list = std::get<Index>(m_ClientLocalDataSyncList)[client_index];
        client_local_list.Clear();
      }

      if constexpr (!std::is_void_v<typename SystemType::ClientLocalEventType>)
      {
        auto & client_event_list = std::get<Index>(m_ClientLocalEvents)[client_index];
        client_event_list.Clear();
      }

      if constexpr (!std::is_void_v<typename SystemType::EffectEventType>)
      {
        auto & effect_event_list = std::get<Index>(m_EffectEvents);
        effect_event_list.RemoveClient(client_index);
      }

      if constexpr (!std::is_void_v<typename SystemType::AuthorityEventType>)
      {
        auto & authority_event_list = std::get<Index>(m_AuthorityEvents);
        authority_event_list.RemoveClient(client_index);
      }
    });
  }

  void Update()
  {
    this->VisitSystems(m_Systems, [&](auto & system, auto index_type)
    {
      constexpr std::size_t Index = std::decay_t<decltype(index_type)>::SystemIndex;
      auto & state = std::get<Index>(m_State);

      using SystemType = std::decay_t<decltype(system)>;
      using Traits = typename SystemType::TraitsType;

      if constexpr(Traits::kWantsUpdate)
      {
        system.Update();
      }

      auto & state_changed_list = std::get<Index>(m_StateSyncList);
      state_changed_list.UpdateState(state, m_CurrentFrame, m_ConnectedClients);

      for(std::size_t client_index = 0; client_index < MaxClients; ++client_index)
      {
        if(m_ConnectedClients.test(client_index))
        {
          auto & client_local = std::get<Index>(m_ClientLocalData)[client_index];
          auto & client_local_changed_list = std::get<Index>(m_ClientLocalDataSyncList)[client_index];

          client_local_changed_list.UpdateState(client_local, m_CurrentFrame);
        }
      }
    });

    m_CurrentFrame++;
  }

  void ForceSyncClient(std::size_t client_index)
  {
    m_ForceSync.set(client_index);
  }

  void ForceSyncAllClients()
  {
    m_ForceSync = m_ConnectedClients;
  }

  template <typename System>
  const typename System::StateType & GetState() const
  {
    constexpr std::size_t Index = this->template GetSystemIndex<System>();
    auto & state = std::get<Index>(m_State);
    return state.Get();
  }

  template <typename System>
  typename System::StateType & GetStateForModify()
  {
    constexpr std::size_t Index = this->template GetSystemIndex<System>();
    auto & state = std::get<Index>(m_State);
    return state.GetForModify();
  }

  template <typename System>
  const typename System::ClientLocalDataType & GetClientLocalData(std::size_t client_index) const
  {
    constexpr std::size_t Index = this->template GetSystemIndex<System>();
    auto & client_local = std::get<Index>(m_ClientLocalData)[client_index];
    return client_local.Get();
  }

  template <typename System>
  typename System::ClientLocalDataType & GetClientLocalDataForModify(std::size_t client_index)
  {
    constexpr std::size_t Index = this->template GetSystemIndex<System>();
    auto & client_local = std::get<Index>(m_ClientLocalData)[client_index];
    return client_local.GetForModify();
  }

  template <typename System, typename T>
  void PushInput(std::size_t client_index, T && input)
  {
    assert(client_index < MaxClients);

    constexpr std::size_t Index = this->template GetSystemIndex<System>();

    auto & system = std::get<Index>(m_Systems);
    system.ProcessInput(client_index, input);
  }

  template <typename System, typename T>
  void PushEffectEvent(T && event, int frame = -1)
  {
    constexpr std::size_t Index = this->template GetSystemIndex<System>();

    auto & event_list = std::get<Index>(m_EffectEvents);
    event_list.PushElement(std::move(event), frame < 0 ? m_CurrentFrame : frame, m_ConnectedClients);
  }

  template <typename System, typename T>
  void PushAuthorityEvent(T && event, int frame = -1)
  {
    constexpr std::size_t Index = this->template GetSystemIndex<System>();

    auto & event_list = std::get<Index>(m_AuthorityEvents);
    event_list.PushElement(std::move(event), frame < 0 ? m_CurrentFrame : frame, m_ConnectedClients);
  }

  template <typename System, typename T>
  void PushExternalEvent(T && event)
  {
    constexpr std::size_t Index = this->template GetSystemIndex<System>();

    auto & system = std::get<Index>(m_Systems);
    system.ProcessExternalEvent(event);
  }

  template <typename System, typename T>
  void PushClientLocalEvent(T && event, std::size_t client_index, int frame = -1)
  {
    constexpr std::size_t Index = this->template GetSystemIndex<System>();

    auto & event_list = std::get<Index>(m_ClientLocalEvents)[client_index];
    event_list.PushElement(std::move(event), frame < 0 ? m_CurrentFrame : frame);
  }

  void SyncFromClient(std::size_t client_index, NetBitReader & reader)
  {
    int client_frame = static_cast<int>(reader.ReadUBits(32));
    this->VisitSystems(m_Systems, [&](auto & system, auto index_type)
    {
      constexpr std::size_t Index = std::decay_t<decltype(index_type)>::SystemIndex;
      using SystemType = std::decay_t<decltype(system)>;
      using InputType = typename SystemType::InputType;

      this->template DeserializeSyncList<4, 24, InputType>(m_CurrentFrame, m_LastClientFrame[client_index], reader,
          [&](auto & input, NetBitReader & reader)
          {
            system.DeserializeInput(input, reader);
          },
          [&](int frame, auto && event)
          {
            system.ProcessInput(client_index, event);
          });
    });
  }

  void SyncToClient(std::size_t client_index, NetBitWriter & writer)
  {
    writer.WriteBits(m_CurrentFrame, 32);

    bool force_sync = m_ForceSync.test(client_index);

    this->VisitSystems(m_Systems, [&](auto & system, auto index_type)
    {
      constexpr std::size_t Index = std::decay_t<decltype(index_type)>::SystemIndex;

      using SystemType = std::decay_t<decltype(system)>;

      auto & state = std::get<Index>(m_State);
      auto & state_changed_list = std::get<Index>(m_StateSyncList);
      this->SerializeMultiStateChangeSyncList(state, force_sync, state_changed_list, client_index, writer, [&](auto & state, NetBitWriter & writer)
      {
        if constexpr(!std::is_void_v<typename SystemType::StateType>)
        {
          system.SerializeState(client_index, state, writer);
        }
      });

      auto & client_local = std::get<Index>(m_ClientLocalData)[client_index];
      auto & client_local_list = std::get<Index>(m_ClientLocalDataSyncList)[client_index];
      this->SerializeStateChangeSyncList(client_local, force_sync, client_local_list, writer, [&](auto & state, NetBitWriter & writer)
      {
        if constexpr(!std::is_void_v<typename SystemType::ClientLocalDataType>)
        {
          system.SerializeClientLocalData(client_index, state, writer);
        }
      });

      auto & client_event_list = std::get<Index>(m_ClientLocalEvents)[client_index];
      this->template SerializeSyncList<4, 24>(client_event_list, m_CurrentFrame, writer, [&](auto & event, NetBitWriter & writer)
      {
        if constexpr(!std::is_void_v<typename SystemType::ClientLocalEventType>)
        {
          system.SerializeClientLocalEvent(client_index, event, writer);
        }
      });

      auto & effect_event_list = std::get<Index>(m_EffectEvents);
      this->template SerializeMultiSyncList<8, 4>(effect_event_list, client_index, m_CurrentFrame, writer, [&](auto & event, NetBitWriter & writer)
      {
        if constexpr(!std::is_void_v<typename SystemType::EffectEventType>)
        {
          system.SerializeEffectEvent(client_index, event, writer);
        }
      });

      auto & authority_event_list = std::get<Index>(m_AuthorityEvents);
      this->template SerializeMultiSyncList<4, 24>(authority_event_list, client_index, m_CurrentFrame, writer, [&](auto & event, NetBitWriter & writer)
      {
        if constexpr(!std::is_void_v<typename SystemType::AuthorityEventType>)
        {
          system.SerializeAuthorityEvent(client_index, event, writer);
        }
      });
    });
  }

  void WriteAck(std::size_t client_index, NetBitWriter & writer)
  {
    writer.WriteBits(m_CurrentFrame, 32);
  }

  void AckFromClient(std::size_t client_index, NetBitReader & reader)
  {
    int ack_frame = reader.ReadUBits(32);
    Ack(client_index, ack_frame);
  }

  void ImmediateAck(std::size_t client_index)
  {
    Ack(client_index, m_CurrentFrame);
  }

protected:

  void Ack(std::size_t client_index, int frame)
  {
    m_ForceSync.reset(client_index);
    this->VisitSystems(m_Systems, [&](auto & system, auto index_type)
    {
      constexpr std::size_t Index = std::decay_t<decltype(index_type)>::SystemIndex;

      using SystemType = std::decay_t<decltype(system)>;
      using Traits = typename SystemType::TraitsType;

      if constexpr (!std::is_void_v<typename SystemType::StateType>)
      {
        auto & state_sync = std::get<Index>(m_StateSyncList);
        state_sync.AckClient(client_index, frame);
      }

      if constexpr (!std::is_void_v<typename SystemType::ClientLocalDataType>)
      {
        auto & client_local_sync = std::get<Index>(m_ClientLocalDataSyncList)[ client_index ];
        client_local_sync.Ack(frame);
      }

      if constexpr (!std::is_void_v<typename SystemType::ClientLocalEventType>)
      {
        auto & client_local_events = std::get<Index>(m_ClientLocalEvents)[ client_index ];
        client_local_events.Ack(frame);
      }

      if constexpr (!std::is_void_v<typename SystemType::EffectEventType>)
      {
        auto & effect_event_list = std::get<Index>(m_EffectEvents);
        effect_event_list.AckClient(client_index, frame);
      }

      if constexpr (!std::is_void_v<typename SystemType::AuthorityEventType>)
      {
        auto & authority_event_list = std::get<Index>(m_AuthorityEvents);
        authority_event_list.AckClient(client_index, frame);
      }
    });
  }

private:
  int m_CurrentFrame = 0;

  // Stores whether each client slot has a connected client
  std::bitset<MaxClients> m_ConnectedClients;
  // Stores whether each client has a requested force sync
  std::bitset<MaxClients> m_ForceSync;

  // Stores the last frame each client ack'd
  int m_LastClientFrame[MaxClients] = {};

  // The actual systems themselves
  std::tuple<Systems...> m_Systems;

  // The states of each system
  std::tuple<NetCOWPtr<typename Systems::StateType>...> m_State;
  // Stores a record of when each state changes so that syncing states that haven't changed can be avoided
  std::tuple<NetStateChangedMultiSyncList<Systems::TraitsType::kSyncStateOnlyIfChanged, MaxClients, typename Systems::StateType>...> m_StateSyncList;

  // Data pertaining to each system that only the associated client knows about
  std::tuple<typename std::array<NetCOWPtr<typename Systems::ClientLocalDataType>, MaxClients>...> m_ClientLocalData;
  // Stores a record of when each client local data changes so that syncing states that haven't changed can be avoided
  std::tuple<typename std::array<NetStateChangedSyncList<Systems::TraitsType::kSyncClientLocalOnlyIfChanged, typename Systems::ClientLocalDataType>, MaxClients>...> m_ClientLocalDataSyncList;

  // Stores a list of all events that the client may simulate
  std::tuple<NetMultiSyncList<typename Systems::EffectEventType, MaxClients>...> m_EffectEvents;
  // Stores a list of all events that only the server may trigger
  std::tuple<NetMultiSyncList<typename Systems::AuthorityEventType, MaxClients>...> m_AuthorityEvents;

  // Stores a list of events that only are sent to an individual client
  std::tuple<typename std::array<NetSyncList<typename Systems::ClientLocalEventType>, MaxClients>...> m_ClientLocalEvents;
};
