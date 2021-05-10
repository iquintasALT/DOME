#pragma once
#include <vector>
#include "game_scene.h"
#include "../game/constant_variables.h"
#include "../ecs/Component.h"


class LoreScene : public GameScene
{
private:
public:
	LoreScene(Game* g) : GameScene(g, "Lore") {};

	void init() override;

	void update();

	void StartGame(Manager* mngr);
};

