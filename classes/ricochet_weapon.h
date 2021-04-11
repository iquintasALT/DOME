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

	int getChargerBullets() { return actcharger; }
private:
	Transform* playerTr;
	int ntier;
	int damage;
	int charger = 30; //Pasar por referencia cuando este
	int actcharger = 30;
	int nbullets = 50;
	int nbounce;
};
