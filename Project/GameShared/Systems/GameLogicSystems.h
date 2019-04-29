#pragma once

#include "Runtime/Collision/CollisionDatabase.h"

#include "GameShared/Systems/CVCPushSystem.h"
#include "GameShared/Systems/TargetDatabase.h"

class GameLogicSystems
{
public:
  GameLogicSystems(const StaticCollisionDatabase & static_collision);

  CollisionDatabase & GetCollisionDatabase();
  CVCPushSystem & GetCVCPushSystem();
  TargetDatabase & GetTargetDatabase();

private:
  CollisionDatabase m_CollisionDatabase;
  CVCPushSystem m_CVCPushSystem;
  TargetDatabase m_TargetDatabase;
};
