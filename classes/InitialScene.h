#pragma once

#include "game_scene.h"
class InitialScene : public GameScene
{
public:
	InitialScene(Game* game): GameScene(game, string("First encounter")){}
	void init();

	void update() override;
};

