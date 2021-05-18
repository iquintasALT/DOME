#pragma once
#include "../components/weapon.h"
#include "../utils/checkML.h"

class WeaponAnimation;
class Entity;
class ChargeWeapon : public Weapon
{
	enum ChargeState {not_charged, winding_up, charged};
private:
	static int bulletsInMagazine;
	ChargeState chargeState = not_charged;
	int tier;
	WeaponAnimation* animator_ = nullptr;
protected:
	Entity* createBullet(const Vector2D& direction) override;
public:
	ChargeWeapon(float fR, int dam, int tier, WeaponAnimation* animator);
	int getBulletsInMagazine() override { return bulletsInMagazine; };
	void setBulletsInMagazine(int bullets) override { bulletsInMagazine = bullets; };
	virtual void update();
	virtual void upgradeCurrentWeapon(int tier) override;
};

