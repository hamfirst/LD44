
#include "StormNetSys/NetEventReconciler.h"

#include <algorithm>


bool NetEventReconcilerBase::PushEventHash(const NetEventHash & event_hash, int frame)
{
  if(event_hash.m_EventHash == 0)
  {
    return true;
  }

  auto itr = std::remove_if(m_HistoryEvents.begin(), m_HistoryEvents.end(),
      [&](const EventInfo & event) { return frame - event.m_Frame > kMaxEventHistory; });

  m_HistoryEvents.erase(itr, m_HistoryEvents.end());

  for(auto & event : m_HistoryEvents)
  {
    if(event.m_EventType != event_hash.m_EventType || event.m_EventHash != event_hash.m_EventHash)
    {
      continue;
    }

    if(std::abs(event.m_PositionX - event_hash.m_PositionX) > m_MaxDist || std::abs(event.m_PositionY - event_hash.m_PositionY) > m_MaxDist)
    {
      continue;
    }

    if(std::abs(event.m_Frame - frame) > m_MaxTime)
    {
      continue;
    }

    return false;
  }

  EventInfo new_event;
  new_event.m_EventType = event_hash.m_EventType;
  new_event.m_EventHash = event_hash.m_EventHash;
  new_event.m_PositionX = event_hash.m_PositionX;
  new_event.m_PositionY = event_hash.m_PositionY;
  new_event.m_Frame = frame;

  m_HistoryEvents.push_back(new_event);
  return true;
}

