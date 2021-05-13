#pragma once
#include "../components/weapon.h"
#include "../utils/checkML.h"
#include "../components/Transform.h"
#include "../sdlutils/Texture.h"

class RicochetWeapon: public Weapon
{
public:
	//El fireRate en este arma es el tiempo que tienes que mantener pulsado el raton
	inline RicochetWeapon(float fR, int dam, Transform* player, int bounce, int tier) : Weapon(fR, dam), playerTr(player), ntier(tier), nbounce(bounce) {};
	virtual void update();

	
	virtual void upgradeTier(int tier);

private:
	Transform* playerTr;
	Texture* tex_ = &sdlutils().images().at("ricochet_projectile");
	int ntier;
	int impactDamage;
	int nbounce;
};
