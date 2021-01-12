#pragma once

#include <tuple>
#include <type_traits>

#include "StormNetSys/NetCOWPtr.h"
#include "StormNetSys/NetServerSystemEmptyTypes.refl.h"

class NetBitWriter;
class NetBitReader;

enum class NetSystemSerializeStateType
{
  kNone,
  kSerializeLatest,
  kSerializeLastAck,
};

struct NetSystemDefaultTraits
{
  static constexpr bool kWantsUpdate = true;
  static constexpr NetSystemSerializeStateType kSerializeState = NetSystemSerializeStateType::kSerializeLastAck;
  static constexpr bool kSerializeInputs = true;
  static constexpr bool kSerializeEvents = true;
  static constexpr bool kSyncStateOnlyIfChanged = true;
  static constexpr bool kSyncClientLocalOnlyIfChanged = true;
};

template <typename State>
struct NetServerSystemStateProcessor
{
  virtual void SerializeState(std::size_t target_client, const State & state, NetBitWriter & writer) const;
  virtual void DeserializeState(State & state, NetBitReader & reader) const;

  virtual NetCOWPtr<State> CreateInitialState()
  {
    if constexpr (std::is_default_constructible_v<State>)
    {
      NetCOWPtr<State> state;
      state.Emplace();
      return state;
    }

    assert(std::is_default_constructible_v<State>);
    return {};
  }
};

template <>
struct NetServerSystemStateProcessor<void>
{

};

template <typename Input, int MaxClients>
struct NetServerSystemInputProcessor
{
  virtual void ProcessInput(std::size_t client_index, const Input & input)
  {

  }

  virtual void SerializeInput(const Input & input, NetBitWriter & writer) const;
  virtual void SerializeInput(std::size_t target_client, const Input & input, NetBitWriter & writer) const;
  virtual void DeserializeInput(Input & input, NetBitReader & reader) const;
};

template <int MaxClients>
struct NetServerSystemInputProcessor<void, MaxClients>
{

};

template <typename State>
struct NetServerSystemClientLocalDataProcessor
{
  virtual void SerializeClientLocalData(std::size_t target_client, const State & state, NetBitWriter & writer) const;
  virtual void DeserializeClientLocalData(State & state, NetBitReader & reader) const;
};

template <>
struct NetServerSystemClientLocalDataProcessor<void>
{

};

template <typename Event>
struct NetServerSystemClientLocalEventProcessor
{
  virtual void SerializeClientLocalEvent(std::size_t target_client, const Event & event, NetBitWriter & writer) const;
  virtual void DeserializeClientLocalEvent(Event & event, NetBitReader & reader) const;
};

template <>
struct NetServerSystemClientLocalEventProcessor<void>
{

};

template <typename Event>
struct NetServerSystemEffectEventProcessor
{
  virtual void SerializeEffectEvent(std::size_t target_client, const Event & event, NetBitWriter & writer) const;
  virtual void DeserializeEffectEvent(Event & event, NetBitReader & reader) const;
};

template <>
struct NetServerSystemEffectEventProcessor<void>
{

};


template <typename Event>
struct NetServerSystemAuthorityEventProcessor
{
  virtual void SerializeAuthorityEvent(std::size_t target_client, const Event & event, NetBitWriter & writer) const;
  virtual void DeserializeAuthorityEvent(Event & event, NetBitReader & reader) const;
};

template <>
struct NetServerSystemAuthorityEventProcessor<void>
{

};

template <typename Event>
struct NetServerSystemExternalEventProcessor
{
  virtual void ProcessExternalEvent(const Event & event)
  {

  }

  virtual void SerializeExternalEvent(std::size_t target_client, const Event & event, NetBitWriter & writer) const;
  virtual void DeserializeExternalEvent(Event & event, NetBitReader & reader) const;
};

template <>
struct NetServerSystemExternalEventProcessor<void>
{

};

template <int MaxClients,
    typename Traits = NetSystemDefaultTraits,
    typename State = void,
    typename Input = void,
    typename EffectEvent = void,
    typename AuthorityEvent = void,
    typename ClientLocalData = void,
    typename ClientLocalEvent = void,
    typename ExternalEvent = void>
class NetServerSystemHandler : public NetServerSystemStateProcessor<State>,
                               public NetServerSystemInputProcessor<Input, MaxClients>,
                               public NetServerSystemClientLocalDataProcessor<ClientLocalData>,
                               public NetServerSystemClientLocalEventProcessor<ClientLocalEvent>,
                               public NetServerSystemEffectEventProcessor<EffectEvent>,
                               public NetServerSystemAuthorityEventProcessor<AuthorityEvent>,
                               public NetServerSystemExternalEventProcessor<ExternalEvent>
{
public:

  using TraitsType = Traits;
  using StateType = State;
  using InputType = Input;
  using EffectEventType = EffectEvent;
  using AuthorityEventType = AuthorityEvent;
  using ClientLocalDataType = ClientLocalData;
  using ClientLocalEventType = ClientLocalEvent;
  using ExternalEventType = ExternalEvent;

  virtual void Update()
  {

  }

  virtual void AddClient(std::size_t client_index)
  {

  }

  virtual void RemoveClient(std::size_t client_index)
  {

  }

  bool IsAuthority() const
  {
    return m_IsAuthority;
  }

  template <typename U = State, typename ReturnType = std::enable_if_t<!std::is_void_v<U>, U>>
  const ReturnType & GetState() const
  {
    return m_State->Get();
  }

  template <typename U = State, typename ReturnType = std::enable_if_t<!std::is_void_v<U>, U>>
  ReturnType & GetStateForModify()
  {
    return m_State->GetForModify();
  }

  template <typename U = ClientLocalData, typename ReturnType = std::enable_if_t<!std::is_void_v<U>, U>>
  const ReturnType & GetClientLocalData(std::size_t client_index) const
  {
    assert(client_index < MaxClients);
    assert(m_ClientLocalData != nullptr);

    return m_ClientLocalData[client_index].Get();
  }

  template <typename U = ClientLocalData, typename ReturnType = std::enable_if_t<!std::is_void_v<U>, U>>
  ReturnType & GetClientLocalDataForModify(std::size_t client_index)
  {
    assert(client_index < MaxClients);
    assert(m_ClientLocalData != nullptr);

    return m_ClientLocalData[client_index].GetForModify();
  }

private:

  template <typename ... Systems>
  friend class NetServerSystemManagerBase;

  bool m_IsAuthority = false;
  NetCOWPtr<State> * m_State = nullptr;
  NetCOWPtr<ClientLocalData> * m_ClientLocalData = nullptr;
};
