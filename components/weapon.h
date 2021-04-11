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
	Transform* playerTr;
	Transform* entityTr;
	Image* entityImg;

	int damage;
	bool flipped;
	float counter;
	float fireRate;

	int charger = 30; //Pasar por referencia cuando este
	int actcharger = 30;
	int nbullets = 50;

public:
	Weapon(float fR, int dam);

	~Weapon();

	virtual int getChargerBullets() { return actcharger; }

	virtual void init();

	virtual void update();

	int getDamage() { return damage; }
	void setDamage(int damage_) { damage = damage_; }

	void adjustToCrouching();
};
