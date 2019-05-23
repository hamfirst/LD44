#pragma once

#include "Runtime/Event/EventSystem.h"
#include "Runtime/ServerEntity/ServerEntity.h"

class GameLogicContainer;

extern template class EventSystem<ServerEntity, ServerEntityHandle>;

class ServerEntityEventSystem : public EventSystem<ServerEntity, ServerEntityHandle>
{

};
