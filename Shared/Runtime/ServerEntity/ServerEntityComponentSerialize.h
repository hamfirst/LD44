#pragma once

#include "Runtime/ServerEntity/ServerEntityComponent.h"

template <typename BaseClass, typename BaseConfig, typename NetBitWriter>
struct NetSerializer<ServerEntityComponent<BaseClass, BaseConfig>, NetBitWriter>
{
  void operator()(const ServerEntityComponent<BaseClass, BaseConfig> & val, NetBitWriter & writer)
  {

  }
};

template <typename BaseClass, typename BaseConfig, typename NetBitReader>
struct NetDeserializer<ServerEntityComponent<BaseClass, BaseConfig>, NetBitReader>
{
  void operator()(ServerEntityComponent<BaseClass, BaseConfig> & val, NetBitReader & reader)
  {

  }
};


