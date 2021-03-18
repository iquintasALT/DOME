#pragma once

#include "../ecs/Component.h"
#include "../game/checkML.h"
#include <math.h>

class Transform;
class Image;

class Weapon: public Component
{
public:
	Weapon(float fR) : fireRate(fR), flipped(false), counter(0) {}

	virtual void init();

	virtual void update();

private:
	Transform* playerTr;
	Transform* entityTr;
	Image* entityImg;

	bool flipped;
	float counter;
	float fireRate;
};
