
#include "GameShared/GameSharedCommon.h"
#include "GameShared/Systems/GameLogicSystems.h"

GameLogicSystems::GameLogicSystems(const StaticCollisionDatabase & static_collision) :
  m_CollisionDatabase(static_collision)
{

}

CollisionDatabase & GameLogicSystems::GetCollisionDatabase()
{
  return m_CollisionDatabase;
}

CVCPushSystem & GameLogicSystems::GetCVCPushSystem()
{
  return m_CVCPushSystem;
}

TargetDatabase & GameLogicSystems::GetTargetDatabase()
{
  return m_TargetDatabase;
}