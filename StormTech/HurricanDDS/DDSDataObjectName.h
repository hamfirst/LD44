#pragma once

#include <cstdint>

#include <StormRefl/StormReflMetaInfoBase.h>

template <class T>
uint32_t DDSDataObjectGetNameHash()
{
  return StormReflTypeInfo<T>::GetNameHash();
}

template <>
inline uint32_t DDSDataObjectGetNameHash<void>()
{
  return 0;
}

