#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../components/Transform.h"
#include "../game/constant_variables.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../components/Image.h"
#include "../sdlutils/SDLUtils.h"

#include <math.h>

class Weapon: public Component
{
public:
	Weapon(float fR) : fireRate(fR), flipped(false), counter(0) {}

	virtual void init() {
		playerTr = entity_->getMngr()->getHandler<Player_hdlr>()->getComponent<Transform>();
		entityTr = entity_->getComponent <Transform>();
		assert(entityTr != nullptr && playerTr != nullptr);

		entityImg = entity_->getComponent<Image>();
		assert(entityImg != nullptr);
		entityImg->setRotationOrigin(0, entityTr->getH() / 2);
	}

	virtual void update();

private:
	Transform* playerTr;
	Transform* entityTr;
	Image* entityImg;

	bool flipped;
	float counter;
	float fireRate;
};

