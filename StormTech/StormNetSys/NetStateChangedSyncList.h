#pragma once

#include "NetCOWPtr.h"
#include "NetSyncList.h"

template <bool SyncOnlyIfChanged, typename T>
class NetStateChangedSyncList
{
public:

  void UpdateState(const NetCOWPtr<T> & state, int frame)
  {
    if constexpr (SyncOnlyIfChanged)
    {
      m_List.PushElement(state != m_PrevState, frame);
      m_PrevState = state;
    }
  }

  void Ack(int frame)
  {
    if constexpr (SyncOnlyIfChanged)
    {
      m_List.Ack(frame);
    }
  }

  void Clear()
  {
    if constexpr (SyncOnlyIfChanged)
    {
      m_PrevState.Clear();
      m_List.Clear();
    }
  }

  bool AnyChanged() const
  {
    if constexpr (SyncOnlyIfChanged)
    {
      bool any_changed = false;
      m_List.VisitElements([&](int frame, char changed)
      {
        any_changed |= static_cast<bool>(changed);
      });

      return any_changed;
    }
    else
    {
      return true;
    }
  }

private:
  NetCOWPtr<T> m_PrevState;
  NetSyncList<std::conditional_t<SyncOnlyIfChanged, char, void>> m_List;
};

template <bool SyncOnlyIfChanged>
class NetStateChangedSyncList<SyncOnlyIfChanged, void>
{
public:
  void UpdateState(const NetCOWPtr<void> & state, int frame) { }

  void Ack(int frame) { }

  void Clear() { }

  bool AnyChanged() const { return false; }
};


template <bool SyncOnlyIfChanged, std::size_t MaxClients, typename T>
class NetStateChangedMultiSyncList
{
public:

  void UpdateState(const NetCOWPtr<T> & state, int frame, const std::bitset<MaxClients> & connected_clients)
  {
    if constexpr (SyncOnlyIfChanged)
    {
      m_List.PushElement(state != m_PrevState, frame, connected_clients);
      m_PrevState = state;
    }
  }

  void RemoveClient(std::size_t client_index)
  {
    if constexpr (SyncOnlyIfChanged)
    {
      m_List.RemoveClient(client_index);
    }
  }

  void AckClient(std::size_t client_index, int frame)
  {
    if constexpr (SyncOnlyIfChanged)
    {
      m_List.AckClient(client_index, frame);
    }
  }

  bool AnyChanged(std::size_t client_index) const
  {
    if constexpr (SyncOnlyIfChanged)
    {
      bool any_changed = false;
      m_List.VisitElementsForClient(client_index, [&](int frame, char changed)
      {
        any_changed |= static_cast<bool>(changed);
      });

      return any_changed;
    }
    else
    {
      return true;
    }
  }

private:
  NetCOWPtr<T> m_PrevState;
  NetMultiSyncList<std::conditional_t<SyncOnlyIfChanged, char, void>, MaxClients> m_List;
};

template <bool SyncOnlyIfChanged, std::size_t MaxClients>
class NetStateChangedMultiSyncList<SyncOnlyIfChanged, MaxClients, void>
{
public:
  void UpdateState(const NetCOWPtr<void> & state, int frame, const std::bitset<MaxClients> & connected_clients) { }

  void RemoveClient(std::size_t client_index) { }

  void AckClient(std::size_t client_index, int frame) { }

  bool AnyChanged(std::size_t client_index) const { return false; }
};