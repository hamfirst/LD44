#pragma once

#include "Foundation/Common.h"
#include "Runtime/Event/Event.h"

class ServerEntity;

class GameLogicContainer;

class ServerEntityEventDispatch
{
public:
  bool TriggerEventHandler(NotNullPtr<ServerEntity> ent, uint32_t type, const void * ev, const EventMetaData & meta);

  template <typename ServerEntityType, typename EventType>
  void RegisterEventHandler(bool (ServerEntityType::* handler)(const EventType &, const EventMetaData & meta))
  {
    using Handler = bool (ServerEntityType::*)(const EventType &, const EventMetaData &);

    EventHandlerInfo handler_info;
    handler_info.m_Type = EventType::TypeNameHash;
    handler_info.m_Callback = [](NotNullPtr<ServerEntity> obj, const void * ev, void * func, const EventMetaData & meta)
    {
      Handler * handler_mem = reinterpret_cast<Handler *>(func);
      auto handler = *handler_mem;

      NotNullPtr<ServerEntityType> ptr = static_cast<NotNullPtr<ServerEntityType>>(obj);
      return (ptr->*handler)(*static_cast<const EventType *>(ev), meta);
    };

    Handler * handler_mem = reinterpret_cast<Handler *>(handler_info.m_Buffer);
    *handler_mem = handler;

    m_EventHandlers.emplace_back(std::move(handler_info));
  }

private:

  using FuncType = void (ServerEntity::*)(GameLogicContainer &);

  struct EventHandlerInfo
  {
    uint32_t m_Type;
    bool(*m_Callback)(NotNullPtr<ServerEntity> obj, const void * ev, void * func, const EventMetaData & meta);

    alignas(alignof(FuncType)) char m_Buffer[sizeof(FuncType)];
  };

  std::vector<EventHandlerInfo> m_EventHandlers;
};



