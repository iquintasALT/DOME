#pragma once
#include "game_scene.h"
#include "enemy.h"
#include "player.h"
#include "tile.h"
#include "../utils/checkML.h"

#include <string>

class RaidScene : public GameScene
{
private:
	string path_;
public:
	RaidScene(string path, string name, Game* game) : GameScene(game, name) { path_ = path;}
	void init() override;
	void update() override;
};

