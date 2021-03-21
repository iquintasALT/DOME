#pragma once
#include "../components/weapon.h"


class RicochetWeapon: public Weapon
{
public:
	RicochetWeapon(float fR) : Weapon(fR) {}; //El fireRate en este arma es el tiempo que tienes que mantener pulsado el raton
	virtual void update();
};

