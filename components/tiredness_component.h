#pragma once
#include "player_health_component.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "../game/checkML.h"
#include "../utils/Vector2D.h"

const float MAX_TIREDNESS = 100;

class TirednessComponent : public PlayerHealthComponent
{
public:
	TirednessComponent(Vector2D position_) : tiredness(MAX_TIREDNESS), t(nullptr), position(position_), tirednessTime(sdlutils().currRealTime()){};
	void init() override;
	void update() override;
	void render() override;

	void sleep(float tiredness_);
private:
	float tiredness;
	Texture* t;
	Vector2D position;
	int tirednessTime;
};

