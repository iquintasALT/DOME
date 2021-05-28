#pragma once

#include "game_scene.h"

#include <vector>

#include "../ecs/Component.h"

class Game;
class Texture;

const array<string, consts::NUM_LOCATIONS> paths = { "./resources/tilemap/zona_nuclear_power_station.tmx",
	"./resources/tilemap/zona_supermarket.tmx", "./resources/tilemap/zona_comunications.tmx", 
	"./resources/tilemap/zona_hospital.tmx", "./resources/tilemap/zona_shop.tmx" };

const array<string, consts::NUM_LOCATIONS> names = { "NUCLEAR POWER STATION", "SUPERMARKET", "COMMUNICATIONS", "HOSPITAL", "SHOP" };

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

	//Foco y linea de trayecto
	Entity* focus;
	Entity* shelterImg;
	Entity* travelLine;
	Entity* travelLineAnimation;
	Entity* particles;
	float animationSpeed;

	void loadLocationButtons(int buttons);

public:
	LocationsScene(Game* g) : GameScene(g, "Locations"), focus(nullptr), shelterImg(nullptr), travelLine(nullptr),
											animationSpeed(3), travelLineAnimation(nullptr), particles(nullptr) {};
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
	void addTravelLine();
	void addParticles();
	void setTravelLine(Transform* buttonPos);

	//Animation
	void addTravelLineAnimation();
	void playTravelLineAnimation();
	void updateAnimation();

	void changeToRaid(Game* g, int index);
};