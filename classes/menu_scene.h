#pragma once
#include "game_scene.h"
#include "menu_button.h"
#include "../utils/checkML.h"

using namespace std;

class Manager;

class MenuScene : public GameScene
{
public: 
	MenuScene(Game* game) :GameScene(game, "Menu") {};
	void init() override;
	static void playGame(Manager* mngr);
	static void settings(Manager* mngr);
	static void exit(Manager* mngr);
};

