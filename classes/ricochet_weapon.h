#pragma once
#include "../components/weapon.h"


class RicochetWeapon: public Weapon
{
public:
	RicochetWeapon(float fR) : Weapon(fR) {};
	virtual void update();
};

