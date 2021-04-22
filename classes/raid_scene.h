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
private:
	string path_;
public:
	RaidScene(string path, Game* game): GameScene(game) { path_ = path; }
	void init() override;
	void update() override;
};

