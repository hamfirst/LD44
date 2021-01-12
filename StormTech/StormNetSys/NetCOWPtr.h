
#pragma once

#include <memory>
#include <cassert>


template <typename T>
class NetCOWPtr
{
public:
  using ValueType = T;

  NetCOWPtr() :
      m_PointerInfo(nullptr)
  {

  }

  explicit NetCOWPtr(const T & t) :
      m_PointerInfo(new PointerInfo{1, t})
  {

  }

  explicit NetCOWPtr(T && t) :
      m_PointerInfo(new PointerInfo{1, std::move(t)})
  {

  }

  NetCOWPtr(const NetCOWPtr & rhs) :
      m_PointerInfo(rhs.m_PointerInfo)
  {
    if(m_PointerInfo)
    {
      m_PointerInfo->m_RefCount++;
    }
  }

  NetCOWPtr(NetCOWPtr && rhs) noexcept :
      m_PointerInfo(rhs.m_PointerInfo)
  {
    rhs.m_PointerInfo = nullptr;
  }

  ~NetCOWPtr()
  {
    Clear();
  }

  NetCOWPtr<T> & operator = (const NetCOWPtr<T> & rhs)
  {
    if(m_PointerInfo == rhs.m_PointerInfo)
    {
      return *this;
    }

    Clear();
    m_PointerInfo = rhs.m_PointerInfo;

    if(m_PointerInfo)
    {
      m_PointerInfo->m_RefCount++;
    }

    return *this;
  }

  NetCOWPtr<T> & operator = (NetCOWPtr<T> && rhs) noexcept
  {
    if(m_PointerInfo == rhs.m_PointerInfo)
    {
      return *this;
    }

    Clear();
    m_PointerInfo = rhs.m_PointerInfo;

    rhs.m_PointerInfo = nullptr;
    return *this;
  }

  bool operator == (const NetCOWPtr<T> & rhs) const
  {
    return rhs.m_PointerInfo == m_PointerInfo;
  }

  bool operator != (const NetCOWPtr<T> & rhs) const
  {
    return rhs.m_PointerInfo != m_PointerInfo;
  }

  void Clear()
  {
    if(m_PointerInfo)
    {
      m_PointerInfo->m_RefCount--;
      assert(m_PointerInfo->m_RefCount >= 0);

      if(m_PointerInfo->m_RefCount == 0)
      {
        delete m_PointerInfo;
      }

      m_PointerInfo = nullptr;
    }
  }

  const T * operator -> () const
  {
    assert(m_PointerInfo != nullptr);
    return &m_PointerInfo->m_T;
  }

  const T & Get() const
  {
    assert(m_PointerInfo != nullptr);
    return m_PointerInfo->m_T;
  }

  template <typename ... Args>
  void Emplace(Args && ... args)
  {
    Clear();

    m_PointerInfo = new PointerInfo{1, T(std::forward<Args>(args)...)};
  }

  T & GetForModify()
  {
    assert(m_PointerInfo != nullptr);
    if(m_PointerInfo->m_RefCount == 1)
    {
      return m_PointerInfo->m_T;
    }

    m_PointerInfo = new PointerInfo{1, m_PointerInfo->m_T};
    return m_PointerInfo->m_T;
  }

  bool Valid() const
  {
    return m_PointerInfo != nullptr;
  }


private:

  struct PointerInfo
  {
    int m_RefCount;
    T m_T;
  };

  PointerInfo * m_PointerInfo;
};

template <>
class NetCOWPtr<void>
{
  void Clear() { }
};
