#pragma once
#include "../components/weapon.h"
#include "../utils/checkML.h"


class ChargeWeapon : public Weapon
{
public:
	ChargeWeapon(float fR, int dam);
	virtual void update();
};

