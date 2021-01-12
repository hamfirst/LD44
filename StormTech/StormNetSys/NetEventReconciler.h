#pragma once

#include <vector>
#include <cstdint>

#include "StormRefl/StormReflMetaFuncs.h"

#include "NetCircularBuffer.h"
#include "NetEventHash.h"

class NetEventReconcilerBase
{
public:

  // Returns false if the event was already triggered
  bool PushEventHash(const NetEventHash & event_hash, int frame);
private:

  struct EventInfo : public NetEventHash
  {
    int m_Frame;
  };

  static const int kMaxEventHistory = 60;
  std::vector<EventInfo> m_HistoryEvents;

  int m_MaxDist = 5;
  int m_MaxTime = 3;
};

template <typename T>
struct NetEventHasher
{
  static std::size_t GetHash(const T & t)
  {
    if constexpr (StormReflCheckReflectable<T>::value)
    {
      std::size_t hash = 0xFFFFFFFF;

      StormReflVisitEach(t, [&](auto field_info)
      {
        using MemberType = typename std::decay_t<decltype(field_info)>::member_type;
        hash ^= NetEventHasher<MemberType>::GetHash(field_info.Get());
        hash <<= 1U;
        hash ^= field_info.GetFieldNameHash();
        hash <<= 1U;
      });

      return hash ^ 0xFFFFFFFF;
    }
    else
    {
      return std::hash<T>{}(t);
    }
  }
};

template <typename T>
class NetEventReconciler : public NetEventReconcilerBase
{
public:
  bool PushEvent(const T & t, int frame)
  {
    NetEventHash hash;
    hash.m_EventHash = NetEventHasher<T>::GetHash(t);
    hash.m_EventType = typeid(T).hash_code();
    hash.m_PositionX = 0;
    hash.m_PositionY = 0;

    StormReflVisitField(t, [&](auto field_info){
      if constexpr (std::is_convertible_v<T, int>)
      {
        hash.m_PositionX = static_cast<int>(field_info.Get());
      }
      }, "m_PositionX");

    StormReflVisitField(t, [&](auto field_info){
      if constexpr (std::is_convertible_v<T, int>)
      {
        hash.m_PositionY = static_cast<int>(field_info.Get());
      }
    }, "m_PositionY");

    return PushEventHash(hash, frame);
  }
};

template <>
class NetEventReconciler<void>
{

};
