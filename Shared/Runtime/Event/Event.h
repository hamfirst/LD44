#pragma once

#include "Runtime/RuntimeCommon.h"

#include <hash/Hash.h>

struct Box;

class GameContainer;
class GameLogicContainer;

class ClientEntity;
class ServerEntity;

struct EventMetaData
{
  EventMetaData() = default;

  EventMetaData(NotNullPtr<GameContainer> game_container) :
    m_GameContainer(game_container)
  {

  }


  EventMetaData(NotNullPtr<ClientEntity> entity_src, NotNullPtr<GameContainer> game_container) :
    m_SourceEntity(entity_src), 
    m_GameContainer(game_container)
  {

  }

  EventMetaData(NotNullPtr<ServerEntity> server_object_src, NotNullPtr<GameLogicContainer> game_logic_container) :
    m_SourceServerObject(server_object_src),
    m_GameLogicContainer(game_logic_container)
  {

  }

  EventMetaData(GameLogicContainer & game_logic_container) :
    m_GameLogicContainer(&game_logic_container)
  {

  }

  NullOptPtr<ClientEntity> m_SourceEntity = nullptr;
  NullOptPtr<ServerEntity> m_SourceServerObject = nullptr;
  NullOptPtr<GameContainer> m_GameContainer = nullptr;
  NullOptPtr<GameLogicContainer> m_GameLogicContainer = nullptr;
  NullOptPtr<const Box> m_ActiveAreaStart = nullptr;
  NullOptPtr<const Box> m_ActiveAreaEnd = nullptr;
};


#define DECLARE_EVENT(EventType) static const uint32_t TypeNameHash = COMPILE_TIME_CRC32_STR(#EventType);
