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

	virtual int getChargerBullets() { return actcharger; }
	virtual int getTamCharger() { return charger; }
	virtual int getTotalBullets() { return nbullets - tcharger; }

private:
	Transform* playerTr;
	int ntier;
	int damage;
	int charger = 30; //Pasar por referencia cuando este
	int actcharger = 30;
	int tcharger = actcharger;
	int nbullets = 50;
	int nbounce;

	float recharge = 0;
	bool recharging = false;

};
