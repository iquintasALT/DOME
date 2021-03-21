#include "GravityComponent.h"

void GravityComponent::update() {
	if (!onFloor_)
		entityTr->setVel(Vector2D(entityTr->getVel().getX(), entityTr->getVel().getY() + gravity / consts::FRAME_RATE));
}

void GravityComponent::reachedFloor() {
	if (entityTr->getVel().getY() > consts::FALLING_DMG_SPEED) std::cout << "OUCH, CAI DESDE MUY ALTO Y YOJHAN ES FEO";
	entityTr->setVel(Vector2D(entityTr->getVel().getX(), 0));
	setOnFloor(true);
}