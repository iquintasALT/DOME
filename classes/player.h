#pragma once

#include "game_object.h"
#include "../utils/checkML.h"

class Physiognomy;
class WeaponBehaviour;

class Player : public GameObject
{
protected:
	WeaponBehaviour* weapon;
	Physiognomy* physiognomy;

public:
	Player(Manager* mngr_, Point2D pos);
	Player(const Player* prevPlayer);
	~Player();
	WeaponBehaviour* getCurrentWeapon();
	WeaponBehaviour* equipWeapon(WeaponBehaviour* newWeapon);
	Physiognomy* getPhysiognomy();
};
