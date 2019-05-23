
#include "GameShared/BehaviorTree/BehaviorTree.h"
#include "GameShared/BehaviorTree/States/PlayAnimationBotState.refl.h"
#include "GameShared/BehaviorTree/States/PlayAnimationForTimeBotState.refl.h"
#include "GameShared/BehaviorTree/States/MoveForTimeBotState.refl.h"

#include "GameShared/BehaviorTree/Conditionals/IsDeadBotConditional.refl.h"
#include "GameShared/BehaviorTree/Conditionals/IsAlertedBotConditional.refl.h"
#include "GameShared/BehaviorTree/Conditionals/IsBeingEatenBotConditional.refl.h"

using BT = StormBehaviorTreeTemplateBuilder<BotServerObject, GameLogicContainer>;

inline BT SELECT()
{
  return BT(StormBehaviorNodeType::kSelect);
}

inline BT SEQUENCE()
{
  return BT(StormBehaviorNodeType::kSequence);
}

inline BT RANDOM()
{
  return BT(StormBehaviorNodeType::kRandom);
}

template <typename StateUpdater, typename ... Args>
inline BT STATE(Args && ... args)
{
  return BT(StormBehaviorTreeTemplateStateMarker<StateUpdater>{}, std::forward<Args>(args)...);
}


