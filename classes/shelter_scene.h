#pragma once
#include "../classes/game_scene.h"
#include "../utils/checkML.h"
#include "../classes/crafting_system.h"
#include "../classes/workshop.h"
#include "../classes/sleep_station.h"
#include "../classes/spaceship_station.h"
#include "../ecs/Entity.h"
#include <functional>
#include "../game/constant_variables.h"

class ShelterScene : public GameScene {
private:
	CraftingSystem* craftSys;
	Workshop* mechanical_Workshop;
	Workshop* medical_Workshop;
	SleepStation* sleep_Station;
	SpaceshipStation* spaceshipStation;

	Vector2D mechPos;
	Vector2D mechSize;

	Vector2D medPos;
	Vector2D medSize;

	Vector2D sleepStPos;
	Vector2D sleepStSize;
	Entity* sleepInteractable;
	Entity* sleepImg;

	Vector2D spaceshipStPos;
	Vector2D spaceshipStSize;

	Manager* uselessMngr;
	int actions;

	void createParallaxBackground(int numOfRep) override;

public:
	ShelterScene(Game* game) :GameScene(game, "Shelter") { actions = consts::MAX_ACTIONS; };
	virtual ~ShelterScene() { delete craftSys, delete uselessMngr; };
	void init() override;
	virtual void update();
	virtual void render() override;
	inline int getActions() { return actions; };

	void initMechWs(Vector2D pos, Vector2D size) { mechPos = pos; mechSize = size; };
	void initMedWs(Vector2D pos, Vector2D size) { medPos = pos; medSize = size; };
	void initSleepStation(Vector2D pos, Vector2D size, Entity* interactable) { sleepStPos = pos;  sleepStSize = size; sleepInteractable = interactable; };
	void initSpaceshipStation(Vector2D pos, Vector2D size) { spaceshipStPos = pos; spaceshipStSize = size; };;

	void sleepTransition();

	void useActions(int numActions);
	void addAction();
};