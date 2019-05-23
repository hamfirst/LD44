#pragma once

#include "Foundation/SkipField/SkipFieldIterator.h"
#include "Foundation/Optional/NullOpt.h"

#include "Engine/Entity/ClientEntity.h"
#include "Engine/Audio/VolumeCategory.h"
#include "Engine/Audio/AudioHandle.h"

#include "Engine/ClientComponent/ClientComponentHandle.h"
#include "Engine/ClientComponent/ClientComponentRegistrationMacros.h"

class ClientEntity;
class ClientComponentSystem;
class ClientComponentUpdateBucketList;
class ClientComponentInitData;

template <class AssetType>
class AssetReference;

class AudioAsset;

class VisualEffectInstance;
class VisualEffectDef;
class VisualEffectResource;
using VisualEffectResourcePtr = DocumentResourcePtr<VisualEffectDef, VisualEffectResource>;

typedef NullOptPtr<ClientComponent> (*ClientComponentResolver)(const ClientComponentHandle & handle, void * comp_store);

class ENGINE_EXPORT ClientComponent
{
public:
  ClientComponent();
  virtual ~ClientComponent();

  DECLARE_BASE_CLIENT_COMPONENT;

  NotNullPtr<ClientEntity> GetEntity();
  const NotNullPtr<ClientEntity> GetEntity() const;

  template <typename T>
  NullOptPtr<T> CastTo()
  {
    if (CastToInternal(T::TypeNameHash))
    {
      return static_cast<T *>(this);
    }

    return nullptr;
  }

  template <typename T>
  const NullOptPtr<T> CastTo() const
  {
    if (CastToInternal(T::TypeNameHash))
    {
      return static_cast<const T *>(this);
    }

    return nullptr;
  }

  NullOptPtr<ClientComponent> CastTo(uint32_t type_name_hash);
  NullOptPtr<const ClientComponent> CastTo(uint32_t type_name_hash) const;

  template <typename EventType>
  uint32_t AddEventHandler(Delegate<void, const EventType &> && handler)
  {
    return GetEntity()->m_EventDispatch.AddEventHandler<EventType>(std::move(handler), GetHandle());
  }

  void Destroy();
  bool IsDestroyed();

  int GetBucket() const;
  ClientComponentHandle GetHandle() const;

  AudioHandle PlayAudio(const AssetReference<AudioAsset> & asset_ref, VolumeCategory cat = VolumeCategory::kSoundEffects, float volume = 1.0f, float pan = 0.0f, bool looping = false);

  NotNullPtr<VisualEffectInstance> CreateVisualEffect(const VisualEffectResourcePtr & fx_resource);
  NotNullPtr<VisualEffectInstance> CreateVisualEffect(const VisualEffectResourcePtr & fx_resource, int layer, const Vector2f & pos);

protected:

  void InitComponentStore(void * comp_store);
  void * GetComponentSore();

private:

  friend class ClientEntity;
  friend class ClientComponentSystem;

  template <typename Type>
  friend class SkipField;

  void SetOwner(NotNullPtr<ClientEntity> entity);
  virtual void OnActivate();
  virtual void OnDestroy();
  virtual void ServerUpdate();
  virtual void ServerDestroy();

  void SetHandle(Handle & handle);
  void SetIterator(const SkipFieldIterator & itr);
  const SkipFieldIterator & GetIterator() const;

  void SetBucket(int bucket);

private:

  NullOptPtr<ClientEntity> m_Entity; // This is set to nullptr when the component has been destroyed
  NotNullPtr<ClientComponentSystem> m_ComponentSystem;
  
  int m_Bucket;

  ClientComponentHandle m_Handle;
  SkipFieldIterator m_Iterator;

};

template <typename T>
NullOptPtr<T> ComponentCast(NotNullPtr<ClientComponent> comp)
{
  return comp->CastTo<T>();
}
