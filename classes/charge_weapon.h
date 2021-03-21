#pragma once
#include "../components/weapon.h"


class ChargeWeapon : public Weapon
{

public:
	ChargeWeapon(float fR) : Weapon(fR) {};
	virtual void update();
};

