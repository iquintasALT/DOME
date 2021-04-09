#pragma once
#include "game_scene.h"
#include "enemy.h"
#include "ranged_enemy.h"
#include "player.h"
#include "tile.h"
#include "../utils/checkML.h"

#include <string>

class RaidScene : public GameScene
{
public:
	 void init() override;
};

