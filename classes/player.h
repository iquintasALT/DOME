#pragma once

#include "../ecs/Entity.h"
#include "../utils/checkML.h"
#include "../utils/Vector2D.h"

class Physiognomy;
class WeaponBehaviour;

class Player : public Entity
{
private:
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
