#pragma once
#include "../classes/game_scene.h"
#include "../utils/checkML.h"
#include "../classes/crafting_system.h"
#include "../classes/workshop.h"
#include "../classes/sleep_station.h"
#include <sdlgui/screen.h>
#include <functional>


class ShelterScene : public GameScene {
private:
	sdlgui::ListImages craftIcons;
	CraftingSystem* craftSys;
	Workshop* mechanical_Workshop;
	Workshop* medical_Workshop;
	SleepStation* sleep_Station;
	Manager* uselessMngr;

public:
	ShelterScene(Game* game) :GameScene(game, "Shelter") {};
	virtual ~ShelterScene() { delete craftSys, delete uselessMngr; };
	void init() override;
	virtual void update();
	virtual void render() override;
};