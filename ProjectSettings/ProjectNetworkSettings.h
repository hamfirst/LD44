#pragma once

#define NET_MODE_SERVER_AUTH                1
#define NET_MODE_GGPO                       2
#define NET_MODE_LOCKSTEP                   3

#define NET_MODE NET_MODE_GGPO

#if NET_MODE == NET_MODE_GGPO
//#define NET_MODE_GGPO_SLIDING_WINDOW
#endif

#define NET_BACKEND_WEBSOCKET 0
#define NET_BACKEND_WEBRTC    1
#define NET_BACKEND_ENET      2

#define NET_BACKEND   NET_WEBSOCKET

#define NET_USE_RANDOM
#define NET_USE_PLAYER_LIMIT
#define NET_USE_TIME_LIMIT
#define NET_USE_SCORE_LIMIT
#define NET_USE_ROUNDS
#define NET_USE_ROUND_TIMER
#define NET_USE_AIM_DIRECTION
#define NET_USE_SCORE
//#define NET_USE_LOADOUT
#define NET_ALLOW_LATE_JOIN
#define NET_LATE_JOIN_REMOVE_BOT
#define NET_LATE_JOIN_ADD_BOT
#define NET_ALLOW_OBSERVERS
#define NET_ALLOW_LOADOUT_CHANGE_AFTER_START
#define NET_FILL_WITH_BOTS
#define NET_USE_READY
#define NET_USE_READY_PRIVATE_GAME
#define NET_FORCE_CASUAL_GAMES
//#define NET_USE_MAP_SELECTION
//#define NET_USE_OFFLINE_STAGING
#define NET_ALLOW_OFFLINE_GAME
#define NET_ALLOW_TUTORIAL

#define NET_SYNC_OLD_STATE
#define NET_SYNC_HISTORY_FRAMES 2
#define NET_SYNC_SERVER_RATE 3

static const int kMaxPlayers = 8;
static const int kMaxTeams = 8;
static const int kMaxLocalPlayers = 4;

static const int kMaxLatency = 160;
static const int kMaxGamesPerServer = 10;