#pragma once

#include "GameShared/SkillTree/SkillTreeConfig.refl.h"
#include "GameShared/SkillTree/SkillTreeCompiled.h"

class SkillTree
{
public:

  SkillTree(NotNullPtr<SkillTreeConfig> config);
  SkillTree(const SkillTree & rhs) = default;
  SkillTree & operator = (const SkillTree & rhs) = default;

  std::string_view GetInternalName(int skill_index) const;
  std::string_view GetDisplayName(int skill_index) const;
  std::string_view GetDescription(int skill_index) const;
  int GetPointsInCategoryRequired(int skill_index) const;
  int GetNumSkills() const;

  bool IsSkillCompletelyPurchased(int skill_index) const;
  bool IsSkillAvailableForPurchase(int skill_index) const;
  int GetTotalCostOfSkill(int skill_index);
  int GetNumRanksUnlocked(int skill_index) const;
  int GetCostOfRanksUnlocked(int skill_index) const;
  int GetCostOfNextRank(int skill_index) const;

  uint64_t GetRawUnlockMask() const;
  void SetRawUnlockMask(uint64_t mask);

  template <typename Visitor>
  void VisitElementsByCategory(uint32_t category_name_hash, Visitor && visitor)
  {
    m_Config->VisitElementsByCategory(category_name_hash, std::forward<Visitor>(visitor));
  }

  template <typename Visitor>
  void VisitPreRequisites(int skill_index, Visitor && visitor)
  {
    m_Config->VisitPreRequisites(skill_index, std::forward<Visitor>(visitor));
  }

  template <typename Visitor>
  void VisitDependentElements(int skill_index, Visitor && visitor)
  {
    m_Config->VisitDependentElements(skill_index, std::forward<Visitor>(visitor));
  }

  template <typename Visitor>
  void VisitRanksForElement(int skill_index, Visitor && visitor)
  {
    m_Config->VisitDependentElements(skill_index, std::forward<Visitor>(visitor));
  }

private:

  NotNullPtr<SkillTreeCompiled> m_Config;
  uint64_t m_Upgrades = 0;
};
