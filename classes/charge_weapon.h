#pragma once
#include "../components/weapon.h"
#include "../utils/checkML.h"


class ChargeWeapon : public Weapon
{
private:
	int tier;
public:
	ChargeWeapon(float fR, int type);
	virtual void update();
};

