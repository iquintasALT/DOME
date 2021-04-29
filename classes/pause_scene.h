#pragma once
#include "../classes/game_scene.h"
#include <list>

class PauseScene : public GameScene
{
public:
	PauseScene(Game* g) : GameScene(g, "Pause") {};
	~PauseScene() {};
	void init() override;

	static void resume(Manager* mng);
	static void menu(Manager* mng);
	static void settings(Manager* mng);
};

