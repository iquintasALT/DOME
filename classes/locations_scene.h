#pragma once
#include "game_scene.h"
#include "../game/constant_variables.h"
class Game;

class LocationsScene : public GameScene
{
private:

public:
	LocationsScene(Game* g);
	void init() {};
	void render() override;

	static void changeToRaid(Game* g);
	static void changeToRaid2(Game* g);
};

