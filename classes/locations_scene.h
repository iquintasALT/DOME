#pragma once
#include "game_scene.h"
#include "../game/constant_variables.h"
#include <vector>
#include "location_button.h"

class Game;

const array<string, consts::NUM_LOCATIONS> paths = { "./resources/tilemap/template.tmx", "./resources/tilemap/zona_hospital.tmx",
												"C", "D", "E" };
enum BUTTONID { Farmacia, Hospital, Nose2, Nose3 };

class LocationsScene : public GameScene
{
private:
	int buttonNumber = 0;
	bool mouseClick = false;
	LocationButton* button;
	LocationButton* shelter;

public:
	LocationsScene(Game* g);
	void init() override {};
	void render() override;
	void update() override;

	void changeToRaid(Game* g, int index);
	void aux(Game* g);
};

