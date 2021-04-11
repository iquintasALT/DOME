#pragma once
#include "../components/weapon.h"
#include "../utils/checkML.h"


class ChargeWeapon : public Weapon
{
private:
	int charger = 30; //Pasar por referencia cuando este
	int actcharger = 30;
	int nbullets = 50;

public:

	int getChargerBullets() { return actcharger; }
	ChargeWeapon(float fR, int dam);
	virtual void update();
};

