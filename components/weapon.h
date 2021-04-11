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

public:
	Weapon(float fR, int dam);

	~Weapon();

	virtual void init();

	virtual void update();

	int getDamage() { return damage; }
	void setDamage(int damage_) { damage = damage_; }

	void adjustToCrouching();
};
