#pragma once


#include "StormNet/NetReflectionTypeDatabase.h"
#include "StormData/StormDataPath.h"

#include "Foundation/Castable/Castable.h"
#include "Foundation/TypeDatabase/TypeDatabase.h"

class ServerEntityNetBitWriter;
class ServerEntityNetBitReader;

template <typename BaseClass, typename BaseConfig>
class ServerEntityComponent;


struct ServerEntityComponentLogicInfo
{
  uint32_t m_NameHash;
  std::size_t m_TypeId;
  std::size_t m_TypeIndex;
  NotNullPtr<const NetTypeInfo> m_TypeInfo;
};

template <typename DataType, typename LogicType>
struct TypeDatabaseInitLogicInfo<DataType, LogicType, ServerEntityComponentLogicInfo>
{
  static void Process(ServerEntityComponentLogicInfo & logic_type_info)
  {
    logic_type_info.m_NameHash = StormReflTypeInfo<LogicType>::GetNameHash();
    logic_type_info.m_TypeId = typeid(LogicType).hash_code();
    logic_type_info.m_TypeIndex = LogicType::__s_TypeDatabase.template GetClassId<LogicType>();
    logic_type_info.m_TypeInfo = &LogicType::__s_TypeDatabase.template GetTypeInfo<LogicType>();
  }
};

template <typename BaseConfig>
class ServerEntityComponentBase
{
public:
  NullOptPtr<const BaseConfig> GetConfig() const
  {
    return m_Config.Value();
  }

  template <typename T>
  NullOptPtr<const T> GetConfigAs() const
  {
    return m_Config.template CastTo<T>();
  }

  using TypeInfo = ServerEntityComponentLogicInfo;

private:

  template <typename BaseClass, typename BaseConfigT>
  friend class ServerEntityComponent;

  ConstCastable<BaseConfig> m_Config;
};

template <typename BaseClass, typename BaseConfig>
class ServerEntityComponent
{
public:

  static_assert(std::is_base_of_v<ServerEntityComponentBase<BaseConfig>, BaseClass>,
          "ClientComponent type must inherit from ServerEntityComponentBase");

  ServerEntityComponent() :
    m_Entity(nullptr),
    m_TypeInfo(nullptr)
  {

  }

  ServerEntityComponent(const ServerEntityComponent<BaseClass, BaseConfig> & rhs)
  {
    if(rhs.m_Entity == nullptr)
    {
      m_Entity = nullptr;
      m_TypeInfo = nullptr;
    }
    else
    {
      m_TypeInfo = rhs.m_TypeInfo;
      m_Entity = static_cast<BaseClass *>(rhs.m_TypeInfo->m_HeapCreate(m_TypeInfo->m_Allocator));
      m_Config = rhs.m_Config;
      m_Entity->m_Config = m_Config;

      m_TypeInfo->m_Copy(m_Entity, rhs.m_Entity);
    }
  }

  ServerEntityComponent(ServerEntityComponent<BaseClass, BaseConfig> && rhs) noexcept
  {
    m_Entity = rhs.m_Entity;
    m_TypeInfo = rhs.m_TypeInfo;
    m_Config = rhs.m_Config;

    rhs.m_Entity = nullptr;
    rhs.m_TypeInfo = nullptr;
    rhs.m_Config = {};
  }

  ~ServerEntityComponent()
  {
    if(m_Entity)
    {
      m_TypeInfo->m_HeapDestroy(m_Entity, m_TypeInfo->m_Allocator);
    }
  }

  ServerEntityComponent<BaseClass, BaseConfig> & operator = (const ServerEntityComponent<BaseClass, BaseConfig> & rhs)
  {
    if(m_TypeInfo == rhs.m_TypeInfo)
    {
      m_Entity->m_Config = rhs.m_Entity->m_Config;
      m_TypeInfo->m_Copy(m_Entity, rhs.m_Entity);
      return *this;
    }

    if(m_Entity)
    {
      m_TypeInfo->m_HeapDestroy(m_Entity, m_TypeInfo->m_Allocator);
    }

    if(rhs.m_Entity == nullptr)
    {
      m_Entity = nullptr;
      m_TypeInfo = nullptr;
    }
    else
    {
      m_TypeInfo = rhs.m_TypeInfo;
      m_Entity = static_cast<BaseClass *>(rhs.m_TypeInfo->m_HeapCreate(m_TypeInfo->m_Allocator));
      m_Config = rhs.m_Config;
      m_Entity->m_Config = rhs.m_Config;

      m_TypeInfo->m_Copy(m_Entity, rhs.m_Entity);
    }

    return *this;
  }

  ServerEntityComponent<BaseClass, BaseConfig> & operator = (ServerEntityComponent<BaseClass, BaseConfig> && rhs)
  {
    if(m_Entity)
    {
      m_TypeInfo->m_HeapDestroy(m_Entity, m_TypeInfo->m_Allocator);
    }

    m_Entity = rhs.m_Entity;
    m_TypeInfo = rhs.m_TypeInfo;
    m_Config = rhs.m_Config;

    rhs.m_Entity = nullptr;
    rhs.m_TypeInfo = nullptr;
    rhs.m_Config = {};
  }

  void SetFromConfig(NotNullPtr<const BaseConfig> config)
  {
    if(m_Entity != nullptr && config == m_Config.Value())
    {
      return;
    }

    for(auto & elem : m_ConfigInfo)
    {
      if(elem.m_Config.Value() == config)
      {
        if(m_Config.Value() == elem.m_Config.Value())
        {
          return;
        }

        m_TypeInfo = elem.m_TypeInfo;
        m_Entity = static_cast<BaseClass *>(elem.m_TypeInfo->m_HeapCreate(m_TypeInfo->m_Allocator));
        m_Config = elem.m_Config;
        m_Entity->m_Config = elem.m_Config;

        return;
      }
    }

    //ASSERT(false, "Could not locate config for server entity component");

    if(m_Entity)
    {
      m_TypeInfo->m_HeapDestroy(m_Entity, m_TypeInfo->m_Allocator);
      m_Entity = nullptr;
      m_TypeInfo = nullptr;
      m_Config = {};
    }
  }

  static void RegisterConfigType(czstr asset_path, const RPolymorphic<BaseConfig, BaseClass> & poly)
  {
    auto asset_path_hash = crc32lowercase(asset_path);
    auto data_path_hash = crc32(StormDataGetPath(poly));

    auto type_info = TypeDatabase<BaseConfig, BaseClass>::Get().GetTypeInfo(poly.GetTypeNameHash());
    if(type_info == nullptr)
    {
      return;
    }

    for(auto & elem : m_ConfigInfo)
    {
      if(elem.m_AssetPath == asset_path_hash && elem.m_DataPath == data_path_hash)
      {
        elem.m_Config = ConstCastable<BaseConfig>(poly.GetValue(), type_info->ConstCast);
        return;
      }
    }

    ConfigInfo info;
    info.m_AssetPath = asset_path_hash;
    info.m_DataPath = data_path_hash;
    info.m_Config = ConstCastable<BaseConfig>(poly.GetValue(), type_info->ConstCast);
    info.m_TypeIndex = type_info->m_LogicTypeInfo.m_TypeIndex;
    info.m_TypeInfo = type_info->m_LogicTypeInfo.m_TypeInfo;
    m_ConfigInfo.emplace_back(std::move(info));
  }

  NullOptPtr<const BaseConfig> GetConfig() const
  {
    return m_Config.Value();
  }

  template <typename T>
  NullOptPtr<const T> GetConfigAs() const
  {
    return m_Config.template CastTo<T>();
  }

  void Clear()
  {
    if(m_Entity)
    {
      m_TypeInfo->m_HeapDestroy(m_Entity, m_TypeInfo->m_Allocator);
      m_Entity = nullptr;
      m_TypeInfo = nullptr;
      m_Config.Clear();
    }
  }

  void Serialize(ServerEntityNetBitWriter & writer) const
  {
    if(m_Entity == nullptr)
    {
      return;
    }

    m_TypeInfo->m_Serialize(m_Entity, writer);
  }

  void Deserialize(ServerEntityNetBitReader & reader)
  {
    if(m_Entity == nullptr)
    {
      return;
    }

    m_TypeInfo->m_Deserialize(m_Entity, reader);
  }

  NullOptPtr<BaseClass> operator -> ()
  {
    return m_Entity;
  }

  NullOptPtr<const BaseClass> operator -> () const
  {
    return m_Entity;
  }

  BaseClass & operator * ()
  {
    return *m_Entity;
  }

  const BaseClass & operator * () const
  {
    return *m_Entity;
  }

  operator bool () const
  {
    return m_Entity;
  }

private:
  NullOptPtr<BaseClass> m_Entity;
  NullOptPtr<const NetTypeInfo> m_TypeInfo;
  ConstCastable<BaseConfig> m_Config;

  struct ConfigInfo
  {
    uint32_t m_AssetPath;
    uint32_t m_DataPath;
    ConstCastable<BaseConfig> m_Config;
    std::size_t m_TypeIndex;
    NotNullPtr<const NetTypeInfo> m_TypeInfo;
  };

  static inline std::vector<ConfigInfo> m_ConfigInfo;

};

template <typename BaseConfig>
struct StormReflTypeInfo<ServerEntityComponentBase<BaseConfig>>
{
  using MyBase = void;
  static constexpr int fields_n = 0;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "ServerEntity"; }
  static constexpr auto GetNameHash() { return COMPILE_TIME_CRC32_STR("ServerEntity"); }
  static ServerEntity & GetDefault() { static ServerEntityComponentBase<BaseConfig> def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<ServerEntityComponentBase<BaseConfig> *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const ServerEntityComponentBase<BaseConfig> *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<ServerEntityComponentBase<BaseConfig> *>(ptr);
    if(typeid(ServerEntityComponentBase<BaseConfig>).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const ServerEntityComponentBase<BaseConfig> *>(ptr);
    if(typeid(ServerEntityComponentBase<BaseConfig>).hash_code() == type_id_hash) return c;
    return nullptr;
  }
};

template <typename BaseConfig>
struct StormReflFuncInfo<ServerEntityComponentBase<BaseConfig>>
{
  using MyBase = StormRelfEmptyBase;
  static constexpr int funcs_n = 0 + StormReflFuncInfo<MyBase>::funcs_n;
  template <int N> struct func_data_static : public StormReflFuncInfo<MyBase>::func_data_static<N> {};
};
