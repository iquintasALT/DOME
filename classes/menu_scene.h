#pragma once
#include "game_scene.h"
#include "menu_button.h"
#include "../utils/checkML.h"

using namespace std;

class Manager;

class MenuScene : public GameScene
{
private:
	std::list<MenuButton*> buttons;

	Texture* back;
public: 
	MenuScene(Game* game);
	void init() override;
	static void playGame(Manager* mngr);
	static void setting(Manager* mngr);
	static void exit(Manager* mngr);
	void render();
	~MenuScene();
};

