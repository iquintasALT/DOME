#pragma once
#include "../classes/game_scene.h"
#include "../utils/checkML.h"
#include "../classes/crafting_system.h"
#include "../classes/workshop.h"
#include "../classes/sleep_station.h"
#include "../classes/spaceship_station.h"
#include <functional>


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

	Vector2D spaceshipStPos;
	Vector2D spaceshipStSize;

	Manager* uselessMngr;
	const int MAX_ACTIONS = 6;
	int actions;

public:
	ShelterScene(Game* game) :GameScene(game, "Shelter") { actions = MAX_ACTIONS; };
	virtual ~ShelterScene() { delete craftSys, delete uselessMngr; };
	void init() override;
	virtual void update();
	virtual void render() override;
	inline int getActions() { return actions; };

	void initMechWs(Vector2D pos, Vector2D size) { mechPos = pos; mechSize = size; };
	void initMedWs(Vector2D pos, Vector2D size) { medPos = pos; medSize = size; };
	void initSleepStation(Vector2D pos, Vector2D size) { sleepStPos = pos;  sleepStSize = size; };;
	void initSpaceshipStation(Vector2D pos, Vector2D size) { spaceshipStPos = pos; spaceshipStSize = size; };;

	void useAction();
};