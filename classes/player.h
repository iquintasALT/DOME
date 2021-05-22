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
	Player(Player* prevPlayer, Manager* mng);
	~Player();
	WeaponBehaviour* getWeapon();
	WeaponBehaviour* equipWeapon(WeaponBehaviour* newWeapon);
	Physiognomy* getPhysiognomy();
	void setPhysiognomy(Physiognomy* physiognomy_);
};
