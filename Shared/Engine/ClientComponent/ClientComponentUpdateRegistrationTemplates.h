#pragma once

#include "Foundation/Update/UpdateRegistrationTemplates.h"

#include "Engine/ClientComponent/ClientComponentUpdateBucketList.h"

template <typename T>
static void ClientComponentRegisterUpdate(T &t, ClientComponentUpdateBucketList &bucket_list)
{
  RegisterUpdate(t, bucket_list, t.GetBucket());
}
