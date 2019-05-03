
#include "GameShared/SkillTree/SkillTree.h"

SkillTree::SkillTree(NotNullPtr<SkillTreeConfig> config) :
        m_Config(config->GetCompiled())
{

}

std::string_view SkillTree::GetInternalName(int skill_index) const
{
  return m_Config->GetInternalName(skill_index);
}

std::string_view SkillTree::GetDisplayName(int skill_index) const
{
  return m_Config->GetDisplayName(skill_index);
}

std::string_view SkillTree::GetDescription(int skill_index) const
{
  return m_Config->GetDescription(skill_index);
}

int SkillTree::GetPointsInCategoryRequired(int skill_index) const
{
  return m_Config->GetPointsInCategoryRequired(skill_index);
}

int SkillTree::GetNumSkills() const
{
  return m_Config->GetNumElements();
}

bool SkillTree::IsSkillCompletelyPurchased(int skill_index) const
{
  int bit_index = m_Config->GetBitIndexForElement(skill_index);
  int num_ranks = m_Config->GetNumRanks(skill_index);

  if(num_ranks == 0)
  {
    return true;
  }

  auto mask = ((1 << GetRequiredBits(num_ranks)) - 1) << bit_index;
  if((m_Upgrades & mask) == mask)
  {
    return true;
  }

  return false;
}

bool SkillTree::IsSkillAvailableForPurchase(int skill_index) const
{
  if(IsSkillCompletelyPurchased(skill_index))
  {
    return false;
  }

  auto points_required = m_Config->GetPointsInCategoryRequired(skill_index);
  if(points_required > 0)
  {
    int points_in_category = 0;
    m_Config->VisitElementsByCategory(m_Config->GetCategoryNameHash(skill_index), [&](int category_skill_index)
    {
      points_in_category += GetCostOfRanksUnlocked(category_skill_index);
    });

    if(points_in_category < points_required)
    {
      return false;
    }
  }

  bool all_pre_reqs_unlocked = true;
  m_Config->VisitPreRequisites(skill_index, [&](int prereq_skill_index)
  {
    if(IsSkillCompletelyPurchased(prereq_skill_index) == false)
    {
      all_pre_reqs_unlocked = false;
    }
  });

  return all_pre_reqs_unlocked;
}

int SkillTree::GetTotalCostOfSkill(int skill_index)
{
  int total_cost = 0;
  m_Config->VisitRanksForElement(skill_index, [&](int cost, ModifierType, GameNetVal)
  {
    total_cost = cost;
  });

  return total_cost;
}

int SkillTree::GetNumRanksUnlocked(int skill_index) const
{
  int bit_index = m_Config->GetBitIndexForElement(skill_index);
  int num_ranks = m_Config->GetNumRanks(skill_index);

  if(num_ranks == 0)
  {
    return 0;
  }

  auto mask = ((1 << GetRequiredBits(num_ranks)) - 1);
  auto unlocked = (m_Upgrades << bit_index) | mask;

  return std::min(num_ranks, (int)unlocked);
}

int SkillTree::GetCostOfRanksUnlocked(int skill_index) const
{
  auto num_ranks = GetNumRanksUnlocked(skill_index);
  int total_cost = 0;
  for(int index = 0; index < num_ranks; ++index)
  {
    total_cost += m_Config->GetRankInfo(skill_index, index).m_Cost;
  }

  return total_cost;
}

int SkillTree::GetCostOfNextRank(int skill_index) const
{
  int bit_index = m_Config->GetBitIndexForElement(skill_index);
  int num_ranks = m_Config->GetNumRanks(skill_index);

  if(num_ranks == 0)
  {
    return 0;
  }

  auto mask = ((1 << GetRequiredBits(num_ranks)) - 1);
  auto unlocked = (m_Upgrades << bit_index) | mask;

  if(unlocked >= num_ranks)
  {
    return 0;
  }


}

uint64_t SkillTree::GetRawUnlockMask() const
{
  return m_Upgrades;
}

void SkillTree::SetRawUnlockMask(uint64_t mask)
{
  m_Upgrades = mask;
}
