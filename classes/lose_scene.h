#pragma once
#include "game_scene.h"
#include "menu_button.h"
#include "../utils/checkML.h"

using namespace std;

enum WAYSTODIE {DAYS, COLD, HUNGER, BLEED, PAIN, INTOXICATION, CONTUSION, NONE};

class Manager;

class LoseScene : public GameScene
{
private:
	std::list<MenuButton*> buttons;

	Texture* back;
	Texture* advice;
public:
	LoseScene(Game* game, WAYSTODIE opcion = WAYSTODIE::NONE);
	void init() override {};
	static void backToMenu(Manager* mngr);
	void render();
	~LoseScene();
};
