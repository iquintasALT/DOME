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


class ChangeImage : public Component {
public:
	ChangeImage(std::vector<Texture*> textures, float speed, LoreScene* l);
	void update() override;
	void render() override;
private:
	float t, speed, f;
	float width = consts::WINDOW_WIDTH;
	float height = consts::WINDOW_HEIGHT;
	Vector2D position;
	int index;
	std::vector<Texture*> backgrounds;
	Texture* black;
	LoreScene* lore;
};
