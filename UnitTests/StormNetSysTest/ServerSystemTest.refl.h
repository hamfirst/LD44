#pragma once

#include "StormNetSys/NetServerSystemHandler.h"

#include "StormNet/NetReflection.h"

struct ServerSystemTestInitInfo
{
  int m_Test = 0;
};

struct ServerSystemTestState
{
  NET_REFL;
  int m_Frame = 0;
  int m_Inputs = 0;
  int m_ExternalEvents = 0;
};

struct ServerSystemTestClientData
{
  NET_REFL;
  int m_Data = 0;
};

struct ServerSystemTestInput
{
  NET_REFL;
  int m_Data = 0;
};

struct ServerSystemTestEffectEvent
{
  NET_REFL;
  int m_PositionX = 0;
  int m_PositionY = 0;
  int m_Data = 0;
};

struct ServerSystemTestAuthorityEvent
{
  NET_REFL;
  int m_Data = 0;
};

struct ServerSystemTestClientLocalData
{
  NET_REFL;
  int m_Data = 0;
};

struct ServerSystemTestClientLocalEvent
{
  NET_REFL;
  int m_Data = 0;
};

struct ServerSystemTestExternalEvent
{
  NET_REFL;
  int m_Data = 0;
};

class ServerSystemTest : public NetServerSystemHandler<16,
    NetSystemDefaultTraits,
    ServerSystemTestState,
    ServerSystemTestInput,
    ServerSystemTestEffectEvent,
    ServerSystemTestAuthorityEvent,
    ServerSystemTestClientLocalData,
    ServerSystemTestClientLocalEvent,
    ServerSystemTestExternalEvent>
{
public:
  explicit ServerSystemTest(const ServerSystemTestInitInfo & info);

  virtual void Update() final override;
  virtual void ProcessInput(std::size_t client_index, const ServerSystemTestInput & input) final override;
  virtual void ProcessExternalEvent(const ServerSystemTestExternalEvent& event) final override;
};



