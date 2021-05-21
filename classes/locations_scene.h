#pragma once

#include <vector>
#include "game_scene.h"
#include "../game/constant_variables.h"
#include "../ecs/Component.h"

class Game;
class Texture;

const array<string, consts::NUM_LOCATIONS> paths = { "./resources/tilemap/zona_shop.tmx", "./resources/tilemap/zona_nuclear_power_station.tmx",
												"./resources/tilemap/zona_hospital.tmx", "./resources/tilemap/zona_comunications.tmx", 
												"./resources/tilemap/zona_supermarket.tmx" };
const array<string, consts::NUM_LOCATIONS> names = {"SHOP", "NUCLEAR POWER STATION", "HOSPITAL", "COMMUNICATIONS", "SUPERMARKET"};

class LocationsScene : public GameScene
{
private:
	int buttonNumber = 0;
	int lastBackGroundActive = 0;
	bool mouseClick = false;
	vector<Entity*> locations;
	vector<Entity*> infos;
	vector<Entity*> backgrounds;
	vector<Transform*> buttonPositions;
	vector<bool> mouseOverInfo;
	Entity* focus;

	void loadLocationButtons();

public:
	LocationsScene(Game* g) : GameScene(g, "Locations"), focus(nullptr) {};
	~LocationsScene() {};
	void init() override;
	void onLoad() override;
	void update() override;
	void addInfoText(Texture* t, Vector2D pos, int xSize, int ySize);
	void addBackground(Texture* t);

	//Focus
	void addFocus();
	void setFocus(Vector2D position);
	void initFocus();

	void changeToRaid(Game* g, int index);
};

class Fade : public Component {
public:
	Fade(float speed, Texture* t = &sdlutils().images().at("black"));

	virtual void init() override;

	virtual ~Fade() {};

	virtual void update() override;

	void render() override;

	void setAlpha(float alpha);

	inline void setDone(bool d) { done = d; f = 255; t = 0; };
private:
	float t, speed_, f;
	bool done;
	Texture* black_;
	Transform* tr_;
};


