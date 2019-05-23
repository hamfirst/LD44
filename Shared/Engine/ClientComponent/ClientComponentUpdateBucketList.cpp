
#include "Engine/EngineCommon.h"
#include "Engine/ClientComponent/ClientComponentUpdateBucketList.h"

template class UpdateList<ClientComponent, ClientComponentUpdateFunc>;
template class UpdateBucketList<ClientComponent, ClientComponentUpdateFunc>;

