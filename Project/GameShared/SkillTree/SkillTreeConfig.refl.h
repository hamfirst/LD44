#pragma once

#include "GameShared/GameSharedCommon.h"
#include "GameShared/SkillTree/SkillTreeCompiled.h"
#include "GameShared/Modifier/Modifier.refl.h"

class SkillTreeCompiled;

struct SkillTreeRankElement : public ModifierConfigElement
{
  STORM_DATA_DEFAULT_CONSTRUCTION_DERIVED(SkillTreeRankElement);
  RInt m_Cost = 1;
};

struct SkillTreeConfigElement
{
  STORM_DATA_DEFAULT_CONSTRUCTION(SkillTreeConfigElement);
  RString m_InternalName;
  RString m_Category;

  RString m_DisplayName;
  RString m_Description;
  RString m_Icon;

  RString m_ValueName;
  RMergeList<SkillTreeRankElement> m_Ranks;

  RMergeList<RString> m_Prerequisites;
  RInt m_PointsInCategoryRequired;
};

struct SkillTreeConfig
{
public:
  STORM_DATA_DEFAULT_CONSTRUCTION(SkillTreeConfig);
  ~SkillTreeConfig();

  RMergeList<SkillTreeConfigElement> m_Elements;

  NotNullPtr<SkillTreeCompiled> GetCompiled();

private:
  NullOptPtr<SkillTreeCompiled> m_CompiledVersion = nullptr;
};
