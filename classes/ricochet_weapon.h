#pragma once
#include "../components/weapon.h"
#include "../utils/checkML.h"
#include "../components/Transform.h"
#include "../sdlutils/Texture.h"

class RicochetWeapon: public Weapon
{
private:
	int ntier = 0;
	int nbounce = 1;

protected:
	Entity* createBullet(const Vector2D& direction) override;

public:
	inline RicochetWeapon() {};
	inline RicochetWeapon(float rateOfFire, int damage, float bulletSpread = 10.0, int bounce = 3, int tier = 0) : Weapon(rateOfFire, damage, bulletSpread, tier), ntier(tier), nbounce(bounce) {};

	virtual void upgradeCurrentWeapon(int tier) override;

	void init() override;
};
