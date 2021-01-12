#pragma once

#include "NetEventHash.h"

template <typename ClientLocalDataChangeType>
struct NetClientLocalDataHandler
{
  virtual void HandleClientLocalDataChange(const ClientLocalDataChangeType & event) { }
};

template <>
struct NetClientLocalDataHandler<void>
{

};

template <typename ClientLocalEventType>
struct NetClientLocalEventHandler
{
  virtual void HandleClientLocalEvent(const ClientLocalEventType & event) { }
};

template <>
struct NetClientLocalEventHandler<void>
{

};

template <typename EffectEventType>
struct NetClientEffectEventHandler
{
  virtual void HandleEffectEvent(const EffectEventType & event) { }
};

template <>
struct NetClientEffectEventHandler<void>
{

};

template <typename AuthorityEventType>
struct NetClientAuthorityEventHandler
{
  virtual void HandleAuthorityEvent(const AuthorityEventType & event) { }
};

template <>
struct NetClientAuthorityEventHandler<void>
{

};

template <typename System>
struct NetClientSystemHandler :
    public NetClientLocalDataHandler<typename System::ClientLocalDataType>,
    public NetClientLocalEventHandler<typename System::ClientLocalEventType>,
    public NetClientEffectEventHandler<typename System::EffectEventType>,
    public NetClientAuthorityEventHandler<typename System::AuthorityEventType>
{

};

template <typename System>
struct NetClientSystemInfo
{
  using Handler = NetClientSystemHandler<System>;
};

#define DECLARE_CLIENT_SYSTEM_HANDLER(ServerSystem, ClientHandler) \
  template <>                                                      \
  struct NetClientSystemInfo<ServerSystem>                         \
  {                                                                \
    using Handler = ClientHandler;                                 \
  };                                                               \


