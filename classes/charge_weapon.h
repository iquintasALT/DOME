#pragma once
#include "../components/weapon.h"
#include "../utils/checkML.h"

class WeaponAnimation;
class ChargeWeapon : public Weapon
{
	enum ChargeState {not_charged, winding_up, charged};
private:
	static int bulletsInMagazine;
	ChargeState chargeState = not_charged;
	int tier;
	WeaponAnimation* animator_ = nullptr;
public:
	int getBulletsInMagazine() override { return bulletsInMagazine; };
	ChargeWeapon(float fR, int dam, int tier, WeaponAnimation* animator);
	virtual void update();
	virtual void upgradeCurrentWeapon(int tier) override;
};

