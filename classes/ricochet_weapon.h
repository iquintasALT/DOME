#pragma once
#include "../components/weapon.h"
#include "../utils/checkML.h"
#include "../components/Transform.h"

class RicochetWeapon: public Weapon
{
public:
	//El fireRate en este arma es el tiempo que tienes que mantener pulsado el raton
	inline RicochetWeapon(float fR, int dam, Transform* player, int bounce, int tier) : Weapon(fR, dam), playerTr(player), ntier(tier), nbounce(bounce) {};
	virtual void update();

private:
	Transform* playerTr;
	int ntier;
	int nbounce;
};

