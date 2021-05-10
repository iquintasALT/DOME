#pragma once
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/checkML.h"

class Manager;
class HungerComponent;
class TirednessComponent;
class Player;
class Texture;
class ShelterScene;

class ShelterHud : public Entity
{
private:
	HungerComponent* hunger;
	TirednessComponent* tiredness;
	Player* player;
	ShelterScene* shelter;

	Texture* hungerState;
	Texture* tirednessState;
	Texture* clock;

public:
	ShelterHud(Manager* mngr, ShelterScene* shelter);
	void render() override;
};

