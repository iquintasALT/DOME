#pragma once
#include "../components/weapon.h"
#include "../utils/checkML.h"


class ChargeWeapon : public Weapon
{
private:
public:

	ChargeWeapon(float fR, int dam);
	virtual void update();
	virtual void upgradeTier(int tier);
};

