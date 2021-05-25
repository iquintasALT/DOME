#pragma once

#include <vector>
#include "game_scene.h"
#include "../game/constant_variables.h"
#include "../ecs/Component.h"

class Game;
class Texture;

const array<string, consts::NUM_LOCATIONS> paths = { "./resources/tilemap/zona_nuclear_power_station.tmx", "./resources/tilemap/zona_supermarket.tmx",
												"./resources/tilemap/zona_comunications.tmx", "./resources/tilemap/zona_hospital.tmx", 
												"./resources/tilemap/zona_shop.tmx" };
const array<string, consts::NUM_LOCATIONS> names = {"NUCLEAR POWER STATION", "SUPERMARKET", "COMMUNICATIONS", "HOSPITAL", "SHOP",};

const array<float, consts::NUM_LOCATIONS> travelTiredness = { consts::TRAVEL_TO_HOSPITAL_TIREDNESS, consts::TRAVEL_TO_SHOP_TIREDNESS,
consts::TRAVEL_TO_SUPERMARKET_TIREDNESS, consts::TRAVEL_TO_NUCLEAR_POWER_STATION_TIREDNESS, consts::TRAVEL_TO_COMUNICATIONS_TIREDNESS };

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


//Fade

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


