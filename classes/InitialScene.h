#pragma once

#include "game_scene.h"
#include "../components/loot.h"
#include "../ecs/Component.h"
#include "../components/Image.h"
#include <functional>

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
	void setReturnToShelter(GameScene* scene);
private:
	int currentCase;
	void checkMovement();
	void checkJump();
	void checkCrouch();
	void checkShoot();


	Entity* initialCollider;
	Entity* trigger;
	Entity* backToShelter;
	Vector2D triggerPos;
};


class TutorialLoot : public Loot {
public:
	TutorialLoot();
	void init() override;
	void Interact() override;
	void CollisionEnter() override;
};

class TutorialTrigger : public Component {
public:
	void OnTrigger(Entity*) override;
};

class TutorialCameraMovement : public Component {
public:
	TutorialCameraMovement(Vector2D p, std::function<void()> f, float speed) :
	destination(p), function(f), speed(speed) {
	};

	void update() override;

private:
	Vector2D destination;
	float speed;
	std::function<void()> function;
};



class TutorialBackToShelter : public InteractableElement {
public:
	TutorialBackToShelter(GameScene* scene) : InteractableElement("Go back home") {

	}

	//void Interact() override;
};