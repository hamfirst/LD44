#pragma once

#include "Runtime/ServerEntity/ServerEntity.h"
#include "Foundation/Update/UpdateBucketList.h"

class GameLogicContainer;

using ServerEntityUpdateFunc = void (ServerEntity::*)(GameLogicContainer &);

extern template class UpdateList<ServerEntity, ServerEntityUpdateFunc>;

class ServerEntityUpdateList : public UpdateList<ServerEntity, ServerEntityUpdateFunc> {};

