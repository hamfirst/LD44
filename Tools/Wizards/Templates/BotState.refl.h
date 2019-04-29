

#pragma once

#include ""GameShared/GameSharedCommon.h""
#include ""Game/GameFullState.refl.h""

#include ""Game/ServerObjects/Bot/BotServerObject.refl.h""


class {class_name}
{{
public:
  NET_REFL;
  STORM_REFL_NODEFAULT;

  {class_name}();

  void Activate(BotServerObject & bot, GameLogicContainer & container);
  bool Update(BotServerObject & bot, GameLogicContainer & container);

private:

}};

