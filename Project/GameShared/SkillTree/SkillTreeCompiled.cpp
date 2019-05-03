
#include "GameShared/SkillTree/SkillTreeCompiled.h"
#include "GameShared/SkillTree/SkillTreeConfig.refl.h"

SkillTreeCompiled::SkillTreeCompiled(SkillTreeConfig & config)
{
  m_NumElements = config.m_Elements.NumElements();
  m_Elements = new SkillTreeCompiledElement[m_NumElements];

  int element_index = 0;
  int bit_index = 0;

  for(auto elem : config.m_Elements)
  {
    auto & out_elem = m_Elements[element_index];

    out_elem.m_InternalNameHash = crc32(elem.second.m_InternalName);
    out_elem.m_CategoryHash = crc32(elem.second.m_Category);
    out_elem.m_ValueNameHash = crc32(elem.second.m_ValueName);

    WriteOutString(elem.second.m_InternalName, out_elem.m_InternalNameStart, out_elem.m_InternalNameCount);
    WriteOutString(elem.second.m_DisplayName, out_elem.m_DisplayNameStart, out_elem.m_DisplayNameStart);
    WriteOutString(elem.second.m_Description, out_elem.m_DescriptionStart, out_elem.m_DescriptionCount);
    WriteOutString(elem.second.m_Icon, out_elem.m_IconStart, out_elem.m_IconCount);

    int total_ranks = 0;
    out_elem.m_RankStart = m_Ranks.size();
    for(auto rank : elem.second.m_Ranks)
    {
      SkillTreeCompiledRankElement rank_elem;
      rank_elem.m_Type = rank.second.m_Type;
      rank_elem.m_Value = rank.second.m_Value;
      rank_elem.m_Cost = rank.second.m_Cost;
      m_Ranks.emplace_back(rank_elem);
      total_ranks++;
    }
    out_elem.m_RankEnd = m_Ranks.size();
    out_elem.m_RequiredPoints = elem.second.m_PointsInCategoryRequired;
    out_elem.m_BitIndex = bit_index;

    bit_index += GetRequiredBits(total_ranks);
    ++element_index;
  }

  element_index = 0;
  for(auto elem : config.m_Elements)
  {
    for(auto pre_req : elem.second.m_Prerequisites)
    {
      auto pre_req_hash = crc32(pre_req.second);
      int pre_req_index = -1;

      for(int index = 0; index < m_NumElements; ++index)
      {
        if(m_Elements[index].m_InternalNameHash == pre_req_hash)
        {
          pre_req_index = index;
          break;
        }
      }

      if(pre_req_index != -1)
      {
        ASSERT(pre_req_index < kMaxPrereqs, "Too many prerequisites for element of skill tree");
        m_Elements[element_index].m_Prereqs[m_Elements[element_index].m_NumPrereqs] = pre_req_index;
        ++m_Elements[element_index].m_NumPrereqs;
      }
    }

    ++element_index;
  }

  m_TotalBits = bit_index;
}

SkillTreeCompiled::~SkillTreeCompiled()
{
  delete [] m_Elements;
}

uint32_t SkillTreeCompiled::GetCategoryNameHash(int element_index) const
{
  return m_Elements[element_index].m_CategoryHash;
}

uint32_t SkillTreeCompiled::GetInternalNameHash(int element_index) const
{
  return m_Elements[element_index].m_InternalNameHash;
}

uint32_t SkillTreeCompiled::GetValueNameHash(int element_index) const
{
  return m_Elements[element_index].m_ValueNameHash;
}

std::string_view SkillTreeCompiled::GetInternalName(int element_index) const
{
  return GetString(m_Elements[element_index].m_InternalNameStart, m_Elements[element_index].m_InternalNameCount);
}

std::string_view SkillTreeCompiled::GetDisplayName(int element_index) const
{
  return GetString(m_Elements[element_index].m_DisplayNameStart, m_Elements[element_index].m_DisplayNameCount);
}

std::string_view SkillTreeCompiled::GetDescription(int element_index) const
{
  return GetString(m_Elements[element_index].m_DescriptionStart, m_Elements[element_index].m_DescriptionCount);
}

std::string_view SkillTreeCompiled::GetIcon(int element_index) const
{
  return GetString(m_Elements[element_index].m_IconStart, m_Elements[element_index].m_IconCount);
}

const SkillTreeCompiledRankElement & SkillTreeCompiled::GetRankInfo(int element_index, int rank_index) const
{
  return m_Ranks[m_Elements[element_index].m_RankStart + rank_index];
}

int SkillTreeCompiled::GetNumRanks(int element_index) const
{
  return m_Elements[element_index].m_RankEnd - m_Elements[element_index].m_RankStart;
}

int SkillTreeCompiled::GetPointsInCategoryRequired(int element_index) const
{
  return m_Elements[element_index].m_RequiredPoints;
}

int SkillTreeCompiled::GetBitIndexForElement(int element_index) const
{
  return m_Elements[element_index].m_BitIndex;
}

int SkillTreeCompiled::GetNumElements() const
{
  return m_NumElements;
}

int SkillTreeCompiled::GetNumBits() const
{
  return m_TotalBits;
}

void SkillTreeCompiled::WriteOutString(const std::string & str, int16_t & start, int16_t & count)
{
  start = m_StringData.size();
  m_StringData += str;
  count = m_StringData.size() - start;
  m_StringData.push_back(0);
}

std::string_view SkillTreeCompiled::GetString(int16_t start, int16_t count) const
{
  return std::string_view(&m_StringData[start], count);
}


