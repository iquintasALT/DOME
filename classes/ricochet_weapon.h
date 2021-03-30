#pragma once
#include "../components/weapon.h"
#include "../game/checkML.h"
#include "../components/Transform.h"

class RicochetWeapon: public Weapon
{
public:
	//El fireRate en este arma es el tiempo que tienes que mantener pulsado el raton
	inline RicochetWeapon(float fR, Transform* player) : Weapon(fR), playerTr(player) {}; 
	virtual void update();

private:
	Transform* playerTr;
};

