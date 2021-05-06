#pragma once

#include <vector>
#include "game_scene.h"
#include "../game/constant_variables.h"

class Game;

const array<string, consts::NUM_LOCATIONS> paths = { "./resources/tilemap/zona_supermarket.tmx", "./resources/tilemap/zona_shop.tmx",
												"./resources/tilemap/zona_hospital.tmx", "./resources/tilemap/zona_comunications.tmx", 
																					"./resources/tilemap/zona_nuclear_power_station.tmx" };
const array<string, consts::NUM_LOCATIONS> names = {"SUPERMARKET", "SHOP", "HOSPITAL", "COMNUNICATIONS", "NUCLEAR POWER STATION"};

class LocationsScene : public GameScene
{
private:
	int buttonNumber = 0;
	bool mouseClick = false;
	vector<Entity*> locations;
	vector<Entity*> infos;

	void loadLocationButtons();

public:
	LocationsScene(Game* g) : GameScene(g, "Locations") {};
	void init() override;
	void update() override;

	void changeToRaid(Game* g, int index);
	void anActualGoodName(Game* g);
};

