#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "NetServerSystemEmptyTypes.refl.h"


template <>
struct StormReflTypeInfo<NetSystemEmptyClientLocalData>
{
  using MyBase = void;
  static constexpr int fields_n = 0;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "NetSystemEmptyClientLocalData"; }
  static constexpr auto GetNameHash() { return 0x5DE9696B; }
  static constexpr bool HasDefault() { return true; }
  static NetSystemEmptyClientLocalData & GetDefault() { static NetSystemEmptyClientLocalData def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<NetSystemEmptyClientLocalData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const NetSystemEmptyClientLocalData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<NetSystemEmptyClientLocalData *>(ptr);
    if(typeid(NetSystemEmptyClientLocalData).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const NetSystemEmptyClientLocalData *>(ptr);
    if(typeid(NetSystemEmptyClientLocalData).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<NetSystemEmptyState>
{
  using MyBase = void;
  static constexpr int fields_n = 0;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "NetSystemEmptyState"; }
  static constexpr auto GetNameHash() { return 0xA8281B70; }
  static constexpr bool HasDefault() { return true; }
  static NetSystemEmptyState & GetDefault() { static NetSystemEmptyState def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<NetSystemEmptyState *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const NetSystemEmptyState *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<NetSystemEmptyState *>(ptr);
    if(typeid(NetSystemEmptyState).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const NetSystemEmptyState *>(ptr);
    if(typeid(NetSystemEmptyState).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<NetSystemDefaultClientJoinInfo>
{
  using MyBase = void;
  static constexpr int fields_n = 0;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "NetSystemDefaultClientJoinInfo"; }
  static constexpr auto GetNameHash() { return 0xA4057B01; }
  static constexpr bool HasDefault() { return true; }
  static NetSystemDefaultClientJoinInfo & GetDefault() { static NetSystemDefaultClientJoinInfo def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<NetSystemDefaultClientJoinInfo *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const NetSystemDefaultClientJoinInfo *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<NetSystemDefaultClientJoinInfo *>(ptr);
    if(typeid(NetSystemDefaultClientJoinInfo).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const NetSystemDefaultClientJoinInfo *>(ptr);
    if(typeid(NetSystemDefaultClientJoinInfo).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

namespace StormReflFileInfo
{
  struct NetServerSystemEmptyTypes
  {
    static const int types_n = 3;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct NetServerSystemEmptyTypes::type_info<0>
  {
    using type = ::NetSystemEmptyClientLocalData;
  };

  template <>
  struct NetServerSystemEmptyTypes::type_info<1>
  {
    using type = ::NetSystemEmptyState;
  };

  template <>
  struct NetServerSystemEmptyTypes::type_info<2>
  {
    using type = ::NetSystemDefaultClientJoinInfo;
  };

}

