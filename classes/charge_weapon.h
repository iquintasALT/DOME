#pragma once
#include "../components/weapon.h"
#include "../game/checkML.h"


class ChargeWeapon : public Weapon
{
public:
	ChargeWeapon(float fR);
	virtual void update();
};

