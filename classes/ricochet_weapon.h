#pragma once
#include "../components/weapon.h"
#include "../utils/checkML.h"
#include "../components/Transform.h"

class RicochetWeapon: public Weapon
{
public:
	//El fireRate en este arma es el tiempo que tienes que mantener pulsado el raton
	inline RicochetWeapon(float fR, Transform* player, int bounce, int tier) : Weapon(fR), playerTr(player), ntier(tier), nbounce(bounce) { damage = 75 * tier; };
	virtual void update();

private:
	Transform* playerTr;
	int ntier;
	int damage;
	int nbounce;
};

