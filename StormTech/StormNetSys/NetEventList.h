
#pragma once

#include "StormNetSys/NetHistoryList.h"

template <typename T>
struct NetEventList : public NetHistoryList<T>
{

};

template <>
struct NetEventList<void>
{

};
