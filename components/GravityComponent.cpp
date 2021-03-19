#include "GravityComponent.h"

void GravityComponent::update() {
	if (entityTr->getPos().getY() + entityTr->getVel().getY() < 638 - entityTr->getH())
		entityTr->setVel(Vector2D(entityTr->getVel().getX(), entityTr->getVel().getY() + gravity / consts::FRAME_RATE));
	else {
		if (entityTr->getVel().getY() > consts::FALLING_DMG_SPEED) std::cout << "OUCH, CAI DESDE MUY ALTO Y YOJHAN ES FEO";
		entityTr->setVel(Vector2D(entityTr->getVel().getX(), 0));
	}
}