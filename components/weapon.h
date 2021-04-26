#pragma once

#include "../ecs/Component.h"
#include "../utils/checkML.h"
#include "../components/KeyboardPlayerCtrl.h"
#include <math.h>

class Transform;
class Image;

class Weapon : public Component
{
protected:
	Entity* player;
	RigidBody* playerRb;
	Transform* playerTr;
	Transform* entityTr;
	Image* entityImg;

	int damage;
	bool flipped;
	float counter;
	float fireRate;

	int charger; //Pasar por referencia cuando este
	int actcharger;
	int nbullets;
	int tcharger;
	float recharge;
	bool recharging;

	float dispersion;

public:
	Weapon(float fR, int dam, float dispersion = 0);

	~Weapon();

	virtual int getChargerBullets() { return actcharger; }
	virtual int getTamCharger() { return charger; }
	virtual int getTotalBullets() { return nbullets - tcharger; }

	virtual void init();

	virtual void update();

	void recharger();
	int getDamage() { return damage; }
	void setDamage(int damage_) { damage = damage_; }

	void adjustToCrouching();
};
