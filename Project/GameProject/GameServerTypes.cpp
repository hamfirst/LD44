#include "GameProject/GameCommon.h"
#include "GameProject/GameServerTypes.h"

template struct NetFixedPointVals<int64_t, 32, 16>;
template class NetFixedPointLUT<int64_t, 32, 16>;

void InitServerTypes()
{
  GameNetLUT::Init();
}
