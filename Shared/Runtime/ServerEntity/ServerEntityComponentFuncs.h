#pragma once

#include "StormRefl/StormRefl.h"
#include "StormRefl/StormReflMetaFuncs.h"

#include "Foundation/TypeDatabase/TypeDatabase.h"

#include "Runtime/ServerEntity/ServerEntityComponent.h"

//ServerEntityComponent<ProjectileMotionBase, ProjectileMotionBaseConfig> m_Motion;
//RPolymorphic<ProjectileMotionBaseConfig, ProjectileMotionBase> m_MotionConfig;

template <typename MemberType, uint32_t member_name_hash, typename Config>
struct ServerEntityInitComponentField
{
  static void Process(MemberType & member, const Config * config)
  {

  }
};


template <typename BaseClass, typename BaseConfig, uint32_t member_name_hash, typename Config>
struct ServerEntityInitComponentField<ServerEntityComponent<BaseClass, BaseConfig>, member_name_hash, Config>
{
  static void Process(ServerEntityComponent<BaseClass, BaseConfig> & member, const Config * config)
  {
    auto visitor = [&](auto f)
    {
      using FieldInfoType = decltype(f);
      using MemberType = typename FieldInfoType::member_type;

      if constexpr (std::template is_same_v<MemberType, RPolymorphic<BaseConfig, BaseClass>> &&
              member_name_hash == FieldInfoType::GetFieldNameHash())
      {
        member.SetFromConfig(f.Get().GetValue());
      }
    };

    StormReflVisitEach(*config, visitor);
  }
};

template <typename ServerEntity, typename Config>
void ServerEntityInitComponents(ServerEntity * entity, const Config * config)
{
  auto visitor = [&](auto f)
  {
    using FieldInfoType = decltype(f);
    using MemberType = typename FieldInfoType::member_type;
    ServerEntityInitComponentField<MemberType, FieldInfoType::GetFieldNameHash(), Config>::Process(f.Get(), config);
  };

  StormReflVisitEach(*entity, visitor);
}
