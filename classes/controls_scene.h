#pragma once
#include "game_scene.h"
#include "menu_button.h"
#include "../utils/checkML.h"

class ControlsScene : public GameScene
{
public:
	ControlsScene(Game* game) : GameScene(game, "Controles") {};
	void init() override;
	void update() override;
};