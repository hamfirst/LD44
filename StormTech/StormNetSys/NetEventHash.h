#pragma once

#include <cstdint>

struct NetEventHash
{
  std::size_t m_EventType = 0;
  uint64_t m_EventHash = 0;
  int m_PositionX = 0;
  int m_PositionY = 0;
};
