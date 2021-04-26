#pragma once
#include "../classes/game_scene.h"
#include <list>
class MenuButton;

class PauseScene : public GameScene
{
public:
	PauseScene(Game* g) : GameScene(g, "Pause") {};
	~PauseScene() {};
	void init() override;

	static void resume(Game* g);
	static void menu(Game* g);
	static void settings(Game* g);
};

