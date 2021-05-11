#pragma once

#include "../ecs/Component.h"
#include "../utils/checkML.h"
#include "../components/KeyboardPlayerCtrl.h"
#include <math.h>


class Transform;
class Image;

enum class WeaponType;
enum ITEMS;
class Weapon : public Component
{
protected:
	Entity* player;
	RigidBody* playerRb;
	Transform* playerTr;
	Transform* entityTr;
	KeyboardPlayerCtrl* ctrl;
	Image* entityImg;

	int damage;
	bool flipped;

	float shootTime; //time between bullets
	float fireRate;

	int chargerSize;
	int remainingBullets;

	Item* currentCharger;

	float rechargeTime;
	bool recharging;

	float dispersion;

	bool ItemIsAmmo(Item* item, WeaponType weaponType);
public:
	Weapon(float fR, int dam, float dispersion = 0);

	~Weapon();

	virtual int getChargerBullets();
	virtual int getChargerSize() { return chargerSize; }
	virtual int getRemainingBullets() { return remainingBullets; }

	virtual void init();

	void setAmmo();

	virtual void update();

	void recharge();
	int getDamage() { return damage; }
	void setDamage(int damage_) { damage = damage_; }

	void adjustToCrouching();
	virtual void upgradeTier(int tier);
};
