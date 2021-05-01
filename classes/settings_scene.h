#pragma once
#include "game_scene.h"
class Game;

class SettingsScene : public GameScene
{
private:

public:
	SettingsScene(Game* g) : GameScene(g, "Settings") {};
	void init() override;
	void update() override;
};

