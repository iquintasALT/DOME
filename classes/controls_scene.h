#pragma once
#include "game_scene.h"
#include "menu_button.h"
#include "../utils/checkML.h"

class ControlsScene : public GameScene
{
private:
	string bgImage = "bgImage";
	string images[4] = { "controls", "locationsTutorial", "raidTutorial", "shelterTutorial" };
	int cont = 1;
	Entity* controls;
public:
	ControlsScene(Game* game) : GameScene(game, "Controles") {};
	void init() override;
	void update() override;
};