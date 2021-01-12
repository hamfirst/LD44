
#pragma once

#include "StormNetSys/NetServerSystemManagerBase.h"
#include "StormNetSys/NetClientSystemHandler.h"
#include "StormNetSys/NetSyncList.h"
#include "StormNetSys/NetEventReconciler.h"

template <typename ... Systems>
class NetServerSystemManagerFullAuthorityClient : public NetServerSystemManagerBase<Systems...>
{
public:

  template <typename ... SystemInit>
  explicit NetServerSystemManagerFullAuthorityClient(SystemInit && ... system_init) :
    m_Systems(std::forward<SystemInit>(system_init)...)
  {
    static_assert(sizeof...(Systems) == sizeof...(SystemInit), "You must provide system init info for all systems");
    this->VisitSystems(m_Systems, [&](auto & system, auto index_type)
    {
      constexpr std::size_t Index = std::decay_t<decltype(index_type)>::SystemIndex;
      auto & state = std::get<Index>(m_State);
      auto & last_state = std::get<Index>(m_LastSyncedState);

      using SystemType = std::decay_t<decltype(system)>;
      using ClientLocalDataType = typename SystemType::ClientLocalDataType;

      state = system.CreateInitialState();
      last_state = state;

      NetCOWPtr<ClientLocalDataType> * empty_client_local = nullptr;

      auto & client_local = std::get<Index>(m_ClientLocalData);

      if constexpr(!std::is_void_v<typename SystemType::ClientLocalDataType>)
      {
        client_local.Emplace();
      }

      this->InitSystem(system, &state, empty_client_local, false);
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
    });

    m_CurrentFrame++;
  }

  template <typename System, typename T>
  void PushInput(T && input)
  {
    constexpr std::size_t Index = this->template GetSystemIndex<System>();
    auto & input_list = std::get<Index>(m_Inputs);

    input_list.PushElement(std::forward<T>(input), m_CurrentFrame);
  }

  template <typename System, typename T>
  void PushEffectEvent(T && event)
  {
    constexpr std::size_t Index = this->template GetSystemIndex<System>();
    auto & event_list = std::get<Index>(m_EffectEventReconciler);
    auto & client_system = std::get<Index>(m_ClientSystems);

    if(event_list.PushEvent(event, m_CurrentFrame))
    {
      client_system.HandleEffectEvent(event);
    }
  }

  template <typename System>
  auto & GetClientSystemHandler()
  {
    constexpr std::size_t Index = this->template GetSystemIndex<System>();
    auto & event_list = std::get<Index>(m_EffectEventReconciler);
    auto & client_system = std::get<Index>(m_ClientSystems);
    return client_system;
  }

  template <typename System, typename T>
  void PushAuthorityEvent(T && event, int frame = -1)
  {
    // Don't handle these on the client
  }

  template <typename System, typename T>
  void PushExternalEvent(T && event)
  {
    // Don't handle these on the client
  }

  template <typename System, typename T>
  void PushClientLocalEvent(T && event, std::size_t client_index, int frame = -1)
  {
    // Don't handle these on the client
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
  const typename System::ClientLocalDataType & GetClientLocalData() const
  {
    constexpr std::size_t Index = this->template GetSystemIndex<System>();
    auto & client_local = std::get<Index>(m_ClientLocalData);
    return client_local.Get();
  }

  void SyncToServer(NetBitWriter & writer) const
  {
    writer.WriteBits(m_CurrentFrame, 32);
    this->VisitSystems(m_Systems, [&](auto & system, auto index_type)
    {
      constexpr std::size_t Index = std::decay_t<decltype(index_type)>::SystemIndex;

      auto & input_list = std::get<Index>(m_Inputs);
      this->template SerializeSyncList<4, 24>(input_list, m_CurrentFrame, writer, [&](auto & input, NetBitWriter & writer)
      {
        system.SerializeInput(input, writer);
      });
    });
  }

  void SyncFromServer(NetBitReader & reader)
  {
    m_CurrentFrame = reader.ReadSBits(32);
    this->VisitSystems(m_Systems, [&](auto & system, auto index_type)
    {
      constexpr std::size_t Index = std::decay_t<decltype(index_type)>::SystemIndex;

      using SystemType = std::decay_t<decltype(system)>;

      auto & client_system = std::get<Index>(m_ClientSystems);

      auto & state = std::get<Index>(m_State);
      auto & last_state = std::get<Index>(m_LastSyncedState);
      this->template DeserializeStateChangeSyncList<SystemType::TraitsType::kSyncStateOnlyIfChanged>(
          state, last_state, reader, [&](auto & state, NetBitReader & reader)
      {
        if constexpr (!std::is_void_v<typename SystemType::StateType>)
        {
          system.DeserializeState(state, reader);
        }
      });

      auto & client_local = std::get<Index>(m_ClientLocalData);
      auto & last_client_local = std::get<Index>(m_LastSyncedClientLocalData);
      this->template DeserializeStateChangeSyncList<SystemType::TraitsType::kSyncClientLocalOnlyIfChanged>(
          client_local, last_client_local, reader, [&](auto & state, NetBitReader & reader)
      {
        if constexpr (!std::is_void_v<typename SystemType::ClientLocalDataType>)
        {
          system.DeserializeClientLocalData(state, reader);
          client_system.HandleClientLocalDataChange(state);
        }
      });

      this->template DeserializeSyncList<4, 24, typename SystemType::ClientLocalEventType>(
          m_CurrentFrame, m_LastServerFrame, reader, [&](auto & event, NetBitReader & reader)
      {
        if constexpr (!std::is_void_v<typename SystemType::ClientLocalEventType>)
        {
          system.DeserializeClientLocalEvent(event, reader);
        }
      },
      [&](int frame, auto && event)
      {
        if constexpr (!std::is_void_v<typename SystemType::ClientLocalEventType>)
        {
          client_system.HandleClientLocalEvent(event);
        }
      });

      auto & event_list = std::get<Index>(m_EffectEventReconciler);
      this->template DeserializeSyncList<8, 4, typename SystemType::EffectEventType>(
          m_CurrentFrame, m_LastServerFrame, reader, [&](auto & event, NetBitReader & reader)
      {
        if constexpr (!std::is_void_v<typename SystemType::EffectEventType>)
        {
          system.DeserializeEffectEvent(event, reader);
        }
      },
      [&](int frame, auto && event)
      {
        if constexpr (!std::is_void_v<typename SystemType::EffectEventType>)
        {
          if (event_list.PushEvent(event, frame))
          {
            client_system.HandleEffectEvent(event);
          }
        }
      });

      this->template DeserializeSyncList<4, 24, typename SystemType::AuthorityEventType>(
          m_CurrentFrame, m_LastServerFrame, reader, [&](auto & event, NetBitReader & reader)
      {
        if constexpr (!std::is_void_v<typename SystemType::AuthorityEventType>)
        {
          system.DeserializeAuthorityEvent(event, reader);
        }
      },
      [&](int frame, auto && event)
      {
        if constexpr (!std::is_void_v<typename SystemType::AuthorityEventType>)
        {
          client_system.HandleAuthorityEvent(event);
        }
      });

    });

    m_LastServerFrame = m_CurrentFrame;
  }

  void WriteAck(NetBitWriter & writer)
  {
    writer.WriteBits(m_CurrentFrame, 32);
  }

  void AckFromServer(NetBitReader & reader)
  {
    int ack_frame = reader.ReadUBits(32);
    Ack(ack_frame);
  }

  void ImmediateAck()
  {
    Ack(m_CurrentFrame);
  }

protected:

  void Ack(int frame)
  {
    this->VisitSystems(m_Systems, [&](auto & system, auto index_type)
    {
      constexpr std::size_t Index = std::decay_t<decltype(index_type)>::SystemIndex;
      auto & input_list = std::get<Index>(m_Inputs);

      input_list.Ack(frame);
    });
  }

private:


  int m_CurrentFrame = 0;
  int m_LastServerFrame = -1;

  std::tuple<Systems...> m_Systems;
  std::tuple<typename NetClientSystemInfo<Systems>::Handler...> m_ClientSystems;

  std::tuple<NetCOWPtr<typename Systems::StateType>...> m_State;
  std::tuple<NetCOWPtr<typename Systems::StateType>...> m_LastSyncedState;
  std::tuple<NetCOWPtr<typename Systems::ClientLocalDataType>...> m_ClientLocalData;
  std::tuple<NetCOWPtr<typename Systems::ClientLocalDataType>...> m_LastSyncedClientLocalData;
  std::tuple<NetSyncList<typename Systems::InputType>...> m_Inputs;
  std::tuple<NetEventReconciler<typename Systems::EffectEventType>...> m_EffectEventReconciler;
};