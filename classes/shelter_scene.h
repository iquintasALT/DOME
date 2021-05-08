#pragma once
#include "../classes/game_scene.h"
#include "../utils/checkML.h"
#include "../classes/crafting_system.h"
#include "../classes/workshop.h"
#include "../classes/sleep_station.h"
#include <functional>


class ShelterScene : public GameScene {
private:
	CraftingSystem* craftSys;
	Workshop* mechanical_Workshop;
	Workshop* medical_Workshop;
	SleepStation* sleep_Station;
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
	void useAction();
};