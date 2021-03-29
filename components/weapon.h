#pragma once

#include "../ecs/Component.h"
#include "../game/checkML.h"
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

	bool flipped;
	float counter;
	float fireRate;

public:
	Weapon(float fR);

	~Weapon();

	virtual void init();

	virtual void update();

	void adjustToCrouching();
};
