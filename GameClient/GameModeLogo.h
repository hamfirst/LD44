#pragma once

#include "Foundation/Time/StopWatch.h"

#include "GameClient/GameMode.h"

class GameModeLogo : public GameMode
{
public:

  virtual void Initialize(GameContainer & container) override;
  virtual void OnAssetsLoaded(GameContainer & container) override;

  virtual void Update(GameContainer & container) override;
  virtual void Render(GameContainer & container) override;

protected:

private:

  StopWatch m_Timer;
};


