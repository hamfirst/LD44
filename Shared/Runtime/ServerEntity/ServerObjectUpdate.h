#pragma once

#include "Runtime/ServerEntity/ServerEntity.h"
#include "Foundation/Update/UpdateBucketList.h"

class GameServerWorld;

using ServerEntityUpdateFunc = void (ServerEntity::*)(GameServerWorld &);

extern template class UpdateList<ServerEntity, ServerEntityUpdateFunc>;

class ServerEntityUpdateList : public UpdateList<ServerEntity, ServerEntityUpdateFunc> {};

