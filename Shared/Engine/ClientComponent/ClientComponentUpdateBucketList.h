#pragma once

#include "Engine/ClientComponent/ClientComponent.h"
#include "Foundation/Update/UpdateBucketList.h"

using ClientComponentUpdateFunc = void (ClientComponent::*)();

extern template class UpdateList<ClientComponent, ClientComponentUpdateFunc>;
extern template class UpdateBucketList<ClientComponent, ClientComponentUpdateFunc>;

class ClientComponentUpdateList : public UpdateList<ClientComponent, ClientComponentUpdateFunc> {};
class ClientComponentUpdateBucketList : public UpdateBucketList<ClientComponent, ClientComponentUpdateFunc> {};

