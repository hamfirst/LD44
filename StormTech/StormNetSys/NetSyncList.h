
#pragma once

#include <vector>
#include <bitset>
#include <algorithm>

// Stores a list of elements until they are ack'd

template <typename T>
class NetSyncList
{
public:

  void PushElement(const T & t, int frame)
  {
    m_Data.emplace_back(SyncData{ frame, t });
  }

  void PushElement(T && t, int frame)
  {
    m_Data.emplace_back(SyncData{ frame, std::move(t) });
  }

  void Ack(int frame)
  {
    auto itr = std::remove_if(m_Data.begin(), m_Data.end(), [&](const SyncData & elem) { return elem.m_Frame <= frame; });
    m_Data.erase(itr, m_Data.end());
  }

  template <typename Visitor>
  void VisitElements(Visitor && visitor)
  {
    for(auto & elem : m_Data)
    {
      visitor(elem.m_Frame, elem.m_T);
    }
  }

  template <typename Visitor>
  void VisitElements(Visitor && visitor) const
  {
    for(auto & elem : m_Data)
    {
      visitor(elem.m_Frame, elem.m_T);
    }
  }

  void Clear()
  {
    m_Data.clear();
  }

private:

  struct SyncData
  {
    int m_Frame;
    T m_T;
  };

  std::vector<SyncData> m_Data;
};

template <>
class NetSyncList<void>
{

};

// Stores a list of elements until they are ack'd by all clients

template <typename T, std::size_t MaxClients>
class NetMultiSyncList
{
public:

  void PushElement(T && t, int frame, const std::bitset<MaxClients> & connected_clients)
  {
    m_Data.emplace_back(SyncData{ connected_clients, frame, std::move(t) });
  }

  void RemoveClient(std::size_t client_index)
  {
    for(auto & elem : m_Data)
    {
      elem.m_DestClients.reset(client_index);
    }

    ClearDeadElements();
  }

  void AckClient(std::size_t client_index, int frame)
  {
    for(auto & elem : m_Data)
    {
      if(elem.m_Frame < frame)
      {
        elem.m_DestClients.reset(client_index);
      }
    }

    ClearDeadElements();
  }

  template <typename Visitor>
  void VisitElementsForClient(std::size_t client_index, Visitor && visitor)
  {
    for(auto & elem : m_Data)
    {
      if(elem.m_DestClients.test(client_index))
      {
        visitor(elem.m_Frame, elem.m_T);
      }
    }
  }

  template <typename Visitor>
  void VisitElementsForClient(std::size_t client_index, Visitor && visitor) const
  {
    for(auto & elem : m_Data)
    {
      if(elem.m_DestClients.test(client_index))
      {
        visitor(elem.m_Frame, elem.m_T);
      }
    }
  }

private:

  void ClearDeadElements()
  {
    auto itr = std::remove_if(m_Data.begin(), m_Data.end(), [](const SyncData & elem) { return !elem.m_DestClients.any(); });
    m_Data.erase(itr, m_Data.end());
  }

private:
  struct SyncData
  {
    std::bitset<MaxClients> m_DestClients;
    int m_Frame;
    T m_T;
  };

  std::vector<SyncData> m_Data;
};

template <std::size_t MaxClients>
struct NetMultiSyncList<void, MaxClients>
{

};

