#pragma once
#include "../components/weapon.h"
#include "../utils/checkML.h"
#include "../components/Transform.h"
#include "../sdlutils/Texture.h"

class RicochetWeapon: public Weapon
{
private:
	static int bulletsInMagazine;
	int ntier = 0;
	int nbounce = 1;

protected:
	Entity* createBullet(const Vector2D& direction) override;

public:
	inline RicochetWeapon(float bulletSpread = 10.0, int bounce = 3, int tier = 0) : Weapon(bulletSpread, tier), ntier(tier), nbounce(bounce) 
	{
		type = RICOCHET;
	};

	int getBulletsInMagazine() override { return RicochetWeapon::bulletsInMagazine; }; 
	void setBulletsInMagazine(int bullets) override { bulletsInMagazine = bullets; };

	void init() override;
};
