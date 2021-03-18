#pragma once
#include "game_scene.h"
#include "menu_button.h"
#include "../game/checkML.h"

class Game;

class MenuScene : public GameScene
{
private:
	std::list<MenuButton*> buttons;

public: 
	MenuScene(Game* g);
	void init() override;
	static void playShelter(Game* g);
	static void playRaid(Game* g);
};

