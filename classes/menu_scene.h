#pragma once
#include "game_scene.h"
#include "menu_button.h"
#include "../utils/checkML.h"
#include <vector>
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



class ScrollingBackGround: public Component {
public:
	ScrollingBackGround(int width, int height, std::vector<Texture*> textures, float speed = 1);

	void update() override;
	void render() override;
private:
	float t, speed;
	float width, height;
	Vector2D currentPos, initialPos, finalPos;

	int index;
	std::vector<Texture*> backgrounds;

	void randomPositions();
};
