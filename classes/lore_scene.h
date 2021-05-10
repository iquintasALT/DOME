#pragma once
#include "../components/weapon.h"
#include "../utils/checkML.h"


class ChargeWeapon : public Weapon
{
private:
public:

	ChargeWeapon(float fR, int dam);
	virtual void update();
	virtual int getChargerBullets() { return actcharger; }
	virtual int getTamCharger() { return charger; }
	virtual int getTotalBullets() { return nbullets - tcharger; }
	virtual void upgradeTier(int tier);
};

