#pragma once
#include "../components/weapon.h"
#include "../utils/checkML.h"


class ChargeWeapon : public Weapon
{
	enum ChargeState {not_charged, winding_up, charged};
private:
	ChargeState chargeState = not_charged;
	int tier;
public:
	ChargeWeapon(float fR, int dam, int tier);
	virtual void update();
	virtual void upgradeCurrentWeapon(int tier) override;
};

