
#pragma once

#include "StormNetSys/NetClientSystemHandler.h"

#include "ServerSystemTest.refl.h"

class ClientSystemTest : public NetClientSystemHandler<ServerSystemTest>
{
public:

  virtual void HandleEffectEvent(const ServerSystemTestEffectEvent & event) override
  {
    m_EffectEvents++;
  }

  virtual void HandleAuthorityEvent(const ServerSystemTestAuthorityEvent & event) override
  {
    m_AuthorityEvents++;
  }

  virtual void HandleClientLocalDataChange(const ServerSystemTestClientLocalData & event) override
  {
    m_ClientLocalDataChanges++;
  }

  virtual void HandleClientLocalEvent(const ServerSystemTestClientLocalEvent & event) override
  {
    m_ClientLocalEvents++;
  }

public:

  int m_EffectEvents = 0;
  int m_AuthorityEvents = 0;
  int m_ClientLocalDataChanges = 0;
  int m_ClientLocalEvents = 0;
};

template <>
struct NetClientSystemInfo<ServerSystemTest>
{
  using Handler = ClientSystemTest;
};

