#pragma once

#include "Foundation/Handle/Handle.h"
#include "Foundation/SkipField/SkipFieldIterator.h"

#include "Runtime/Animation/AnimationState.h"
#include "Runtime/ServerEntity/ServerEntityHandle.h"
#include "Runtime/ServerEntity/ServerEntityRegistrationMacros.h"
#include "Runtime/ServerEntity/ServerEntityEventDispatch.h"
#include "Runtime/ServerEntity/ServerEntityEventSystem.h"
#include "Runtime/ServerEntity/ServerEntityTypeInfo.h"
#include "Runtime/Event/Event.h"

#include "StormRefl/StormReflMetaInfoBase.h"

class ServerEntityManager;
class ServerComponent;
class ServerGameState;

class GameServerWorld;

class ServerEntity
{
public:
  DECLARE_BASE_SERVER_ENTITY;

  ServerEntityHandle GetEntityHandle() const;
  void Destroy(ServerEntityManager & obj_manager);

  virtual void InitPosition(const Vector2 & pos);

  virtual czstr GetDefaultEntityBinding() const;
  virtual czstr GetEntityBinding() const;

  virtual Optional<int> GetAssociatedPlayer(GameServerWorld & game_container) const;
  virtual void InitStaticComponents();

  bool IsDestroyed() const;
  int GetSlotIndex() const;

  int GetLifetime() const;
  int GetTypeIndex() const;

  template <typename Type>
  NullOptPtr<Type> CastTo()
  {
    if (CastToInternal((uint32_t)Type::TypeNameHash))
    {
      return static_cast<Type *>(this);
    }

    return nullptr;
  }

  template <typename EventType>
  bool SendEvent(const EventType & ev, const EventMetaData & meta)
  {
    return TriggerEventHandler(EventType::TypeNameHash, &ev, meta);
  }

  const ServerEntityTypeInfo & GetTypeInfo() const;

  template <typename ComponentType>
  NullOptPtr<ComponentType> GetComponent()
  {
    for(auto & elem : GetTypeInfo().m_ComponentInfo)
    {
      if(elem.m_TypeIdHash == typeid(ComponentType).hash_code())
      {
        return elem.m_Get(this);
      }
    }

    return nullptr;
  }

  template <typename ComponentType>
  NullOptPtr<const ComponentType> GetComponent() const
  {
    for(auto & elem : GetTypeInfo().m_ComponentInfo)
    {
      if(elem.m_TypeIdHash == typeid(ComponentType).hash_code())
      {
        return elem.m_ConstGet(this);
      }
    }

    return nullptr;
  }

  template <typename ComponentType>
  NullOptPtr<ComponentType> FindComponent()
  {
    for(auto & elem : GetTypeInfo().m_ComponentInfo)
    {
      auto ptr = elem.m_Get(this);
      auto comp = elem.m_Cast(typeid(ComponentType).hash_code(), ptr);

      if(comp)
      {
        return comp;
      }
    }

    return nullptr;
  }

  template <typename ComponentType>
  NullOptPtr<const ComponentType> FindComponent() const
  {
    for(auto & elem : GetTypeInfo().m_ComponentInfo)
    {
      auto ptr = elem.m_ConstGet(this);
      auto comp = elem.m_ConstCast(typeid(ComponentType).hash_code(), ptr);

      if(comp)
      {
        return comp;
      }
    }

    return nullptr;
  }

protected:

  void SetEventDispatch(NotNullPtr<ServerEntityEventDispatch> event_dispatch);

private:

  template <typename Type>
  friend class SkipField;

  template <typename EntityType, typename HandleType>
  friend class EventSystem;

  friend class ServerEntitySystem;
  friend class ServerEntityManager;
  friend class GameServerEntityOverlapSystem;

  const Handle & GetHandle() const;
  void SetHandle(Handle & handle);

  void SetIterator(const SkipFieldIterator & itr);
  const SkipFieldIterator & GetIterator() const;

  bool TriggerEventHandler(uint32_t event_type, const void * ev, const EventMetaData & meta);

private:
  bool m_IsStatic = false;
  bool m_IsUnsynced = false;
  bool m_IsDestroyed = false;
  int m_TypeIndex = 0;
  int m_SlotIndex = 0;
  int m_FramesAlive = 0;

  SkipFieldIterator m_Iterator;
  Handle m_Handle;
  ServerEntityHandle m_ServerEntityHandle;

  NullOptPtr<ServerEntityEventDispatch> m_EventDispatch = nullptr;
};

template <typename T>
NullOptPtr<T> ServerEntityHandle::ResolveTo(const ServerEntityManager & entity_manager) const
{
  static_assert(std::is_base_of<ServerEntity, T>::value, "Must resolve to server entity type");

  auto ptr = Resolve(entity_manager);
  if (ptr == nullptr)
  {
    return nullptr;
  }

  if (ptr->CastToInternal((uint32_t)T::TypeNameHash))
  {
    return static_cast<T *>(ptr);
  }

  return nullptr;
}

template <>
NullOptPtr<ServerEntity> ServerEntityHandle::ResolveTo<ServerEntity>(const ServerEntityManager & entity_manager) const;

template <>
struct StormReflTypeInfo<ServerEntity>
{
  using MyBase = void;
  static constexpr int fields_n = 0;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "ServerEntity"; }
  static constexpr auto GetNameHash() { return COMPILE_TIME_CRC32_STR("ServerEntity"); }
  static ServerEntity & GetDefault() { static ServerEntity def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<ServerEntity *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const ServerEntity *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<ServerEntity *>(ptr);
    if(typeid(ServerEntity).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const ServerEntity *>(ptr);
    if(typeid(ServerEntity).hash_code() == type_id_hash) return c;
    return nullptr;
  }
};

template <>
struct StormReflFuncInfo<ServerEntity>
{
  using MyBase = StormRelfEmptyBase;
  static constexpr int funcs_n = 0 + StormReflFuncInfo<MyBase>::funcs_n;
  template <int N> struct func_data_static : public StormReflFuncInfo<MyBase>::func_data_static<N> {};
};