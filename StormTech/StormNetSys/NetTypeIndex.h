
#pragma once

#include <tuple>


template <class T, class Tuple>
struct NetTypeIndex
{

};

template <class T, class... Types>
struct NetTypeIndex<T, std::tuple<T, Types...>>
{
  static const std::size_t value = 0;
};

template <class T, class U, class... Types>
struct NetTypeIndex<T, std::tuple<U, Types...>>
{
  static_assert(sizeof...(Types) != 0, "Failed to find type in tuple type list");
  static const std::size_t value = 1 + NetTypeIndex<T, std::tuple<Types...>>::value;
};

template <class T, class ... Types>
struct NetTypeIndex<T, std::tuple<Types...>>
{
  static_assert(sizeof...(Types) != 0, "Failed to find type in tuple type list");
  static const std::size_t value = static_cast<std::size_t>(-1);
};
