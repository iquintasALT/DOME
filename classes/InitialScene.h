#pragma once

#include "game_scene.h"
#include "../components/loot.h"
#include "../ecs/Component.h"
#include "../components/Image.h"

class Loot;
class InitialScene : public GameScene
{
public:
	InitialScene(Game* game): GameScene(game, string("First encounter")){}
	void init();

	void update() override;
};


class TutorialManager : public Component {
public:
	static TutorialManager* instance;
	Entity* currentMessage;

	void init() override;
	void update() override;
	void changeCase(int);
private:
	int currentCase;
	void checkMovement();
	void checkJump();
	void checkInventory();
	void checkCrouch();
	void checkShoot();
};


class TutorialLoot : public Loot {
public:
	TutorialLoot();
	void init() override;
	void Interact() override;
};