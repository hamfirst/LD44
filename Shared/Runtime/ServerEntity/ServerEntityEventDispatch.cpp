
#include "Runtime/RuntimeCommon.h"
#include "Runtime/ServerEntity/ServerEntityEventDispatch.h"

bool ServerEntityEventDispatch::TriggerEventHandler(NotNullPtr<ServerEntity> ent, uint32_t type, const void * ev, const EventMetaData & meta)
{
  for (auto & handler : m_EventHandlers)
  {
    if (handler.m_Type == type)
    {
      return handler.m_Callback(ent, ev, handler.m_Buffer, meta);
    }
  }

  return true;
}


