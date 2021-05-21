#pragma once
#include "game_scene.h"
#include "menu_button.h"
#include "../utils/checkML.h"
#include "../game/Game.h"
#include <vector>
using namespace std;

class Manager;

class MenuScene : public GameScene
{
private:
	bool firstTime = true;
public:
	MenuScene(Game* game, bool firstTime = true) : GameScene(game, "Menu"), firstTime(firstTime) {};
	void init() override;
	void onLoad() override;
	static void playGame(Manager* mngr);
	static void settings(Manager* mngr);
	static void credits(Manager* mngr);
	static void exit(Manager* mngr);
};



class ScrollingBackGround : public Component {
public:
	ScrollingBackGround(int width, int height, std::vector<Texture*> textures, float speed = 1, bool random = false);
	void update() override;
	void render() override;
private:
	bool random;
	float t, speed, f;
	float width, height;
	Vector2D currentPos, initialPos, finalPos;

	int index;
	std::vector<Texture*> backgrounds;
	Texture* black;

	void randomPositions();
	void changeOrder();
};
