#pragma once

#include "GameShared/GameSharedCommon.h"
#include "GameShared/Modifier/Modifier.refl.h"

static const int kMaxPrereqs = 4;

struct SkillTreeConfig;

struct SkillTreeCompiledElement
{
  uint32_t m_InternalNameHash = 0;
  uint32_t m_CategoryHash = 0;
  uint32_t m_ValueNameHash = 0;
  int16_t m_DisplayNameStart;
  int16_t m_DisplayNameCount;
  int16_t m_InternalNameStart;
  int16_t m_InternalNameCount;
  int16_t m_DescriptionStart;
  int16_t m_DescriptionCount;
  int16_t m_IconStart;
  int16_t m_IconCount;
  int16_t m_RankStart;
  int16_t m_RankEnd;
  int16_t m_Prereqs[kMaxPrereqs];
  int16_t m_NumPrereqs = 0;
  int16_t m_RequiredPoints = 0;
  int16_t m_BitIndex = 0;
};

struct SkillTreeCompiledRankElement : public Modifier
{
  int m_Cost;
};

class SkillTreeCompiled
{
public:
  explicit SkillTreeCompiled(SkillTreeConfig & config);
  ~SkillTreeCompiled();

  uint32_t GetCategoryNameHash(int element_index) const;
  uint32_t GetInternalNameHash(int element_index) const;
  uint32_t GetValueNameHash(int element_index) const;
  std::string_view GetInternalName(int element_index) const;
  std::string_view GetDisplayName(int element_index) const;
  std::string_view GetDescription(int element_index) const;
  std::string_view GetIcon(int element_index) const;
  const SkillTreeCompiledRankElement & GetRankInfo(int element_index, int rank_index) const;
  int GetNumRanks(int element_index) const;
  int GetPointsInCategoryRequired(int element_index) const;
  int GetBitIndexForElement(int element_index) const;
  int GetNumElements() const;
  int GetNumBits() const;

  template <typename Visitor>
  void VisitElementsByCategory(uint32_t category_name_hash, Visitor && visitor)
  {
    for(int index = 0; index < m_NumElements; ++index)
    {
      if(m_Elements[index].m_CategoryHash == category_name_hash)
      {
        visitor(index);
      }
    }
  }

  template <typename Visitor>
  void VisitPreRequisites(int element_index, Visitor && visitor)
  {
    for(int index = 0; index < m_Elements[element_index].m_NumPrereqs; ++index)
    {
      visitor((int)m_Elements[index].m_Prereqs[index]);
    }
  }

  template <typename Visitor>
  void VisitDependentElements(int element_index, Visitor && visitor)
  {
    for(int index = 0; index < m_NumElements; ++index)
    {
      for(int pre_req = 0; pre_req < m_Elements[index].m_NumPrereqs; ++pre_req)
      {
        if(m_Elements[index].m_Prereqs[pre_req] == element_index)
        {
          visitor(index);
        }
      }
    }
  }

  template <typename Visitor>
  void VisitRanksForElement(int element_index, Visitor && visitor)
  {
    for(int index = m_Elements[element_index].m_RankStart; index <  m_Elements[element_index].m_RankEnd; ++index)
    {
      visitor(m_Ranks[index].m_Cost, m_Ranks[index].m_Type, m_Ranks[index].m_Value);
    }
  }

private:

  void WriteOutString(const std::string & str, int16_t & start, int16_t & count);
  std::string_view GetString(int16_t start, int16_t count) const;

private:

  NotNullPtr<SkillTreeCompiledElement> m_Elements;
  std::vector<SkillTreeCompiledRankElement> m_Ranks;
  std::string m_StringData;
  int m_NumElements;
  int m_TotalBits;
};
