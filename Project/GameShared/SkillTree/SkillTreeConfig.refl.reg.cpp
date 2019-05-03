#include "Game/GameCommon.h"
#include "Foundation/SkipField/SkipField.h"

#include "StormRefl/StormReflMetaFuncs.h"
#include "StormRefl/StormReflJsonStd.h"

#include "StormData/StormData.h"
#include "StormData/StormDataJson.h"

#include "Runtime/Config/ConfigRegistrationMacros.h"

#include "Project/GameShared/SkillTree/SkillTreeConfig.refl.h"
#include "Project/GameShared/SkillTree/SkillTreeConfig.refl.meta.h"

REGISTER_CONFIG_TYPE(SkillTreeConfig, "Skill Tree Config", "skilltreeconfig", "Configs");
STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(SkillTreeRankElement);
STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(SkillTreeConfigElement);
STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(SkillTreeConfig);


SkillTreeConfig::~SkillTreeConfig()
{
  if(m_CompiledVersion != nullptr)
  {
    delete m_CompiledVersion;
  }
}

NotNullPtr<SkillTreeCompiled> SkillTreeConfig::GetCompiled()
{
  if(m_CompiledVersion == nullptr)
  {
    m_CompiledVersion = new SkillTreeCompiled(*this);
  }

  return m_CompiledVersion;
}
