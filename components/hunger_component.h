#pragma once
#include "player_health_component.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "../game/checkML.h"
#include "../utils/Vector2D.h"

const float MAX_HUNGER = 100;

class HungerComponent : public PlayerHealthComponent
{
public:
	HungerComponent(Vector2D position_) : hunger(MAX_HUNGER), t(nullptr), position(position_), hungerTime(sdlutils().currRealTime()) {};
	~HungerComponent() { delete t; }
	void init() override;
	void update() override;
	void render() override;

	void eat(float hunger_);
private:
	float hunger;
	Texture* t;
	Vector2D position;
	int hungerTime;
};

