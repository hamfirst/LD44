
#pragma once

#include <memory>
#include <type_traits>

#include "StormRefl/StormReflMetaInfoBase.h"

template <typename Interface, typename ... ConstructArgs>
class ClassDef
{
public:
  static_assert(std::has_virtual_destructor_v<Interface>, "ClassDef interface must have a virtual destructor");

  ClassDef()
  {
    if constexpr(std::is_constructible_v<Interface, ConstructArgs...>)
    {
      return ClassDef(
        [](ConstructArgs ... args) { return std::make_unique<Interface>(std::forward<ConstructArgs>(args)...); },
        StormReflTypeInfo<Interface>::GetNameHash());
    }
  }

private:

  ClassDef(std::unique_ptr<Interface> (*CreateInstanceFunc)(ConstructArgs ... args), uint32_t type_name_hash) :
    m_CreateInstanceFunc(CreateInstanceFunc),
    m_TypeNameHash(type_name_hash)
  {

  }

public:

  template <typename T>
  static ClassDef<Interface, ConstructArgs...> CreateClassDef()
  {
    return ClassDef(
      [](ConstructArgs ... args) { return std::make_unique<T>(std::forward<ConstructArgs>(args)...); },
      StormReflTypeInfo<T>::GetNameHash());
  }

  ClassDef(const ClassDef<Interface, ConstructArgs...> & rhs) = default;
  ClassDef(ClassDef<Interface, ConstructArgs...> && rhs) noexcept = default;

  ClassDef<Interface, ConstructArgs...>  & operator = (const ClassDef<Interface, ConstructArgs...> & rhs) = default;
  ClassDef<Interface, ConstructArgs...>  & operator = (ClassDef<Interface, ConstructArgs...> && rhs) noexcept = default;

  std::unique_ptr<Interface> CreateInstance(ConstructArgs ... args)
  {
    return m_CreateInstanceFunc(std::forward<ConstructArgs>(args)...);
  }

  bool operator == (const ClassDef<Interface, ConstructArgs...>& other_def) const
  {
    return m_TypeNameHash == other_def.m_TypeNameHash;
  }

  bool operator != (const ClassDef<Interface, ConstructArgs...>& other_def) const
  {
    return m_TypeNameHash != other_def.m_TypeNameHash;
  }

  bool operator < (const ClassDef<Interface, ConstructArgs...>& other_def) const
  {
    return m_TypeNameHash < other_def.m_TypeNameHash;
  }

  bool operator <= (const ClassDef<Interface, ConstructArgs...>& other_def) const
  {
    return m_TypeNameHash <= other_def.m_TypeNameHash;
  }

  bool operator > (const ClassDef<Interface, ConstructArgs...>& other_def) const
  {
    return m_TypeNameHash > other_def.m_TypeNameHash;
  }

  bool operator >= (const ClassDef<Interface, ConstructArgs...>& other_def) const
  {
    return m_TypeNameHash <= other_def.m_TypeNameHash;
  }

private:

  std::unique_ptr<Interface> (*m_CreateInstanceFunc)(ConstructArgs ... args) = nullptr;
  uint32_t m_TypeNameHash = 0;
};


