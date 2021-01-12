#pragma once


#include "Foundation/Common.h"

#include "StormNet/NetReflectionStruct.h"
#include "StormNet/NetReflectionTypeDatabase.h"

#include "StormNet/NetReflection.h"
#include "StormNet/NetMessageSender.h"

#include "GameProject/GameServerTypes.h"

#include "ProjectSettings/ProjectNetworkSettings.h"
#include "ProjectSettings/ProjectPerspective.h"

#if PROJECT_PERSPECTIVE == PERSPECTIVE_SIDESCROLLER
#define PLATFORMER_MOVEMENT
#endif

#if (NET_MODE == NET_MODE_GGPO)
static const int kMaxRewindFrames = 20;
static const int kMaxHistoryFrames = 30;
#endif

#ifdef NET_USE_SCORE
static const int kMaxScore = 5;
#endif

#ifdef NET_USE_ROUNDS
static const int kMaxRounds = 15;
#endif

#ifdef NET_USE_ROUND_TIMER

static const int kPreRoundTimer = 60 * 3;
static const int kMaxRoundTimer = 60 * 45;
static const int kPostRoundTimer = 60 * 20;

enum STORM_REFL_ENUM class RoundState
{
  kPreRound,
  kRound,
  kPostRound,
};
#endif

class GameStage;

struct GameInitSettings
{
  NET_REFL;
  uint8_t m_StageIndex = 0;

#ifdef NET_USE_PLAYER_LIMIT
  uint8_t m_PlayerCount = 0;
#endif

#ifdef NET_USE_SCORE_LIMIT
  uint16_t m_ScoreLimit = 0;
#endif

#ifdef NET_USE_SCORE_LIMIT
  uint16_t m_TimeLimit = 0;
#endif
};

// Data sent from the server to the client
struct ClientLocalData
{
  NET_REFL;
  NetRangedNumber<int, -1, kMaxPlayers> m_PlayerIndex = -1;

#ifdef NET_ALLOW_OBSERVERS
  NetRangedNumber<int, -1, kMaxPlayers> m_ObserverIndex = -1;
#endif
};

struct ClientInput
{
  NET_REFL;

#ifdef PLATFORMER_MOVEMENT

  bool m_JumpHeld;
  GameNetVal m_XInput;
  GameNetVal m_YInput;

#else

  GameNetVal m_InputAngle;
  GameNetVal m_InputStr;

#endif

#ifdef NET_USE_AIM_DIRECTION
  GameNetVal m_AimDirection;
#endif
};

// Data sent from the client to the server
struct ClientAuthData
{
  NET_REFL;
  ClientInput m_Input;
};

enum STORM_REFL_ENUM PlayerAIState
{
  kSearchForNPCs,
  kSearchForCover,
  kEscape,
};

struct AITargetPos
{
  NET_REFL;
  GameNetVal x;
  GameNetVal y;
};

struct AIPlayerInfo
{

  NET_REFL;
  PlayerAIState m_State;

  int8_t m_LastSeenPlayer = -1;
  uint8_t m_TimeInLos = 0;
  uint8_t m_TimeOutOfLos = 0;
  uint8_t m_CoverCounter = 0;

  NetOptional<AITargetPos> m_TargetPosition;
};

#ifdef NET_USE_LOADOUT
struct GamePlayerLoadout
{
  NET_REFL;
};
#endif

struct GamePlayer
{
  NET_REFL;

  std::string m_UserName;
  NetRangedNumber<int, 0, kMaxTeams - 1> m_Team;

#ifdef NET_USE_LOADOUT
  GamePlayerLoadout m_Loadout;
#endif
};

struct GameStateLoadingPlayer
{
  NET_REFL;
  std::string m_UserName;
  bool m_Loaded = false;
  NetRangedNumber<int, -1, kMaxTeams - 1> m_Team = 0;

#ifdef NET_USE_LOADOUT
  GamePlayerLoadout m_Loadout;
#endif
};

#ifdef NET_ALLOW_OBSERVERS
struct GameObserver
{
  NET_REFL;
  std::string m_UserName;
};
#endif

struct GameInstanceData
{
  NET_REFL;

  NetSparseList<AIPlayerInfo, kMaxPlayers> m_AIPlayerInfo;

#ifdef NET_USE_SCORE
  NetRangedNumber<int, 0, kMaxScore> m_Score[kMaxTeams];
#endif

  NetOptional<NetRangedNumber<int, -1, kMaxTeams>> m_WiningTeam;

#ifdef NET_USE_ROUNDS
  NetRangedNumber<int, 0, kMaxRounds> m_Round;
#endif

#ifdef NET_USE_ROUND_TIMER
  NetEnum<RoundState> m_RoundState;
  NetRangedNumber<int, 0, kMaxRoundTimer> m_RoundTimer = kMaxRoundTimer;
#endif

#ifdef NET_USE_RANDOM
  NetRandom m_Random;
#endif
};

