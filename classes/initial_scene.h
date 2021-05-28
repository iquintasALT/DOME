#pragma once

#include "game_scene.h"
#include "../components/loot.h"
#include "../ecs/Component.h"
#include "../components/image.h"
#include <functional>

class Loot;
class InitialScene : public GameScene
{
public:
	InitialScene(Game* game): GameScene(game, string("First encounter")){}
	void init();
	void createParallaxBackground(int numOfRep) override;
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
	void checkShoot();


	Entity* initialCollider;
	Entity* trigger;
	Entity* backToShelter;
	Vector2D triggerPos;
	DefaultEnemy* enemy;
};


class TutorialLoot : public Loot {
public:
	TutorialLoot();
	void init() override;
	void Interact() override;
	void CollisionEnter() override;

private:
	bool firstTime;
	bool firstTimeClosing;
};

class TutorialTrigger : public Component {
public:
	TutorialTrigger(int i = 3) : i(i) {};
	void OnTrigger(Entity*) override;
private:
	int i;
};

class TutorialCameraMovement : public Component {
public:
	TutorialCameraMovement(Vector2D p, std::function<void()> f, float speed) : destination(p), function(f), speed(speed) {};

	void update() override;

private:
	Vector2D destination;
	float speed;
	std::function<void()> function;
};

class TutorialBackToShelter : public InteractableElement {
public:
	TutorialBackToShelter(GameScene* scene) : InteractableElement("Go back home") {
		currentScene = scene;
		alreadyPressed = false;
	}

	void Interact() override;
	void changeScene();
private:
	GameScene* currentScene;
	bool alreadyPressed;
	void changeImage(int n, int i);
};