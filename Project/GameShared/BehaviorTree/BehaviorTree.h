
#pragma once

#include "StormBehavior/StormBehaviorTree.h"

class BotServerObject;
class GameServerWorld;

using BotBehaviorTree = StormBehaviorTree<BotServerObject, GameServerWorld>;
