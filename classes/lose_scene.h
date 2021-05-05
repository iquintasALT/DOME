#pragma once
#include "game_scene.h"
#include "menu_button.h"
#include "../utils/checkML.h"

using namespace std;

enum muertes{dias, frio, comida, desangrado};

class Manager;

class Lose_scene : public GameScene
{
private:
	std::list<MenuButton*> buttons;

	Texture* back;
	Texture* advice;
public:
	Lose_scene(Game* game, muertes opcion);
	void init() override {};
	static void GoBackMenu(Manager* mngr);
	void render();
	~Lose_scene();
};
