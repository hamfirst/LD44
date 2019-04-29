
#pragma once

#include "StormRefl/StormRefl.h"

#include <string>
#include <vector>

struct NoiseAlert
{
  STORM_REFL;
  float angle;
  float alpha;
};

struct GameClientUIData
{
  STORM_REFL;

  bool timer_pre_round = false;
  bool timer_post_round = false;
  float timer_scale = 0.0f;
  std::string timer;

  std::string tutorial_hint;
  int tutorial_hint_x = 0;
  int tutorial_hint_y = 0;

  int health = 0;
  int ammo = 0;
  int max_ammo = 0;
  int lives = 0;

  std::vector<NoiseAlert> alerts;
  int num_alerts = 0;
};

struct UpgradeInfo
{
  STORM_REFL;

  int damage = 0;
  int ammo = 0;
  int health = 0;
  int speed = 0;
  int life = 0;
  int rate = 0;
};