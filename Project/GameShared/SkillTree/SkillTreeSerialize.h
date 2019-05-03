
#pragma once

#include "StormNet/NetSerialize.h"
#include "StormNet/NetDeserialize.h"

#include "GameShared/SkillTree/SkillTree.h"


template <typename NetBitWriter>
struct NetSerializer<SkillTree, NetBitWriter>
{
  void operator()(const SkillTree & val, NetBitWriter & writer)
  {
    writer.WriteBits(val.GetRawUnlockMask(), GetRequiredBits(val.GetNumSkills()));
  }
};

template <typename NetBitReader>
struct NetDeserializer<SkillTree, NetBitReader>
{
  void operator()(SkillTree & val, NetBitReader & reader)
  {
    uint64_t unlock_mask = reader.ReadUBits(GetRequiredBits(val.GetNumSkills()));
    val.SetRawUnlockMask(unlock_mask);
  }
};
