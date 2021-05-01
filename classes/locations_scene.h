#pragma once

#include <vector>
#include "game_scene.h"
#include "../game/constant_variables.h"

class Game;

const array<string, consts::NUM_LOCATIONS> paths = { "./resources/tilemap/template.tmx", "./resources/tilemap/zona_comunications.tmx",
												"C", "D", "E" };
const array<string, consts::NUM_LOCATIONS> names = {"template", "hospital", "C", "D", "E"};

enum BUTTONID { Farmacia, Hospital, Nose2, Nose3 };

class LocationsScene : public GameScene
{
private:
	int buttonNumber = 0;
	bool mouseClick = false;
	vector<Entity*> locations;

	void loadLocationButtons();

public:
	LocationsScene(Game* g) : GameScene(g, "Locations") {};
	void init() override;
	void update() override;

	void changeToRaid(Game* g, int index);
	void anActualGoodName(Game* g);
};

