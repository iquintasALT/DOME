#pragma once
#include "game_scene.h"
#include "../game/constant_variables.h"
#include <vector>
class Game;
class LocationButton;

const array<string, consts::NUM_LOCATIONS> paths = { "./resources/tilemap/template.tmx", "./resources/tilemap/zona_hospital.tmx",
												"C", "D", "E" };
enum BUTTONID { Farmacia, Hospital, Nose2, Nose3 };

class LocationsScene : public GameScene
{
public:
	LocationsScene(Game* g);
	void init() {};
	void render() override;

	static void changeToRaid(Game* g, int index);
};

