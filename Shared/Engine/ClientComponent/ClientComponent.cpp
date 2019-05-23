
#include "Engine/EngineCommon.h"

#include "Runtime/ClientComponent/ClientComponentInitData.refl.meta.h"
#include "Runtime/ClientComponent/ClientComponentInitDataTypeDatabase.h"
#include "Runtime/ClientComponent/ClientComponentInitDataTypeDatabaseRegister.h"

#include "Engine/EngineState.h"
#include "Engine/Entity/ClientEntity.h"
#include "Engine/ClientComponent/ClientComponent.h"
#include "Engine/ClientComponent/ClientComponentSystem.h"
#include "Engine/Audio/AudioManager.h"
#include "Engine/VisualEffect/VisualEffectManager.h"

#include "Engine/ClientComponent/ClientComponentList.h"
#include "Engine/ClientComponent/ClientComponentUpdateBucketList.h"
#include "Engine/ClientComponent/ClientComponentUpdateRegistrationTemplates.h"

REGISTER_BASE_CLIENT_COMPONENT(ClientComponent);

ClientComponent::ClientComponent() :
  m_Bucket(0)
{

}

ClientComponent::~ClientComponent()
{

}

NotNullPtr<ClientEntity> ClientComponent::GetEntity()
{
  return m_Entity;
}

const NotNullPtr<ClientEntity> ClientComponent::GetEntity() const
{
  return m_Entity;
}


NullOptPtr<ClientComponent> ClientComponent::CastTo(uint32_t type_name_hash)
{
  if (CastToInternal(type_name_hash))
  {
    return this;
  }

  return nullptr;
}

NullOptPtr<const ClientComponent> ClientComponent::CastTo(uint32_t type_name_hash) const
{
  if (CastToInternal(type_name_hash))
  {
    return this;
  }

  return nullptr;
}

void ClientComponent::Destroy()
{
  OnDestroy();

  m_Entity->RemoveComponentInternal(this);
  m_Entity = nullptr;

  m_ComponentSystem->AddToDeadComponentList(this);
}

bool ClientComponent::IsDestroyed()
{
  return m_Entity == nullptr;
}

int ClientComponent::GetBucket() const
{
  return m_Bucket;
}

ClientComponentHandle ClientComponent::GetHandle() const
{
  return m_Handle;
}

AudioHandle ClientComponent::PlayAudio(const AssetReference<AudioAsset> & asset_ref, VolumeCategory cat, float volume, float pan, bool looping)
{
  return g_AudioManager.PlayAudio(asset_ref, cat, volume, pan, looping);
}

NotNullPtr<VisualEffectInstance> ClientComponent::CreateVisualEffect(const VisualEffectResourcePtr & fx_resource)
{
  return CreateVisualEffect(fx_resource, GetEntity()->GetLayer(), GetEntity()->GetPosition());
}

NotNullPtr<VisualEffectInstance> ClientComponent::CreateVisualEffect(const VisualEffectResourcePtr & fx_resource, int layer, const Vector2f & pos)
{
  auto engine_state = GetEntity()->GetEngineState();
  return engine_state->GetVisualEffectManager()->CreateVisualEffect(fx_resource, layer, pos);
}

void ClientComponent::InitComponentStore(void * comp_store)
{
  m_Handle.m_ComponentStore = comp_store;
}

void * ClientComponent::GetComponentSore()
{
  return m_Handle.m_ComponentStore;
}

void ClientComponent::SetOwner(NotNullPtr<ClientEntity> entity)
{
  m_Entity = entity;
}

void ClientComponent::OnActivate()
{

}

void ClientComponent::OnDestroy()
{

}

void ClientComponent::ServerUpdate()
{

}

void ClientComponent::ServerDestroy()
{

}

void ClientComponent::SetHandle(Handle & handle)
{
  Handle & int_handle = m_Handle;
  int_handle = handle;
  m_Handle.ResolveFunc = GetResolver();
}

void ClientComponent::SetIterator(const SkipFieldIterator & itr)
{
  m_Iterator = itr;
}

const SkipFieldIterator & ClientComponent::GetIterator() const
{
  return m_Iterator;
}

void ClientComponent::SetBucket(int bucket)
{
  m_Bucket = bucket;
}
