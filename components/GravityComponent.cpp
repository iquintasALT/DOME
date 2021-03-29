#include "GravityComponent.h"

GravityComponent::GravityComponent() {
	gravity = consts::GRAVITY;
	onFloor_ = false;
}

void GravityComponent::init() {
	entityTr = entity_->getComponent<Transform>();
	assert(entityTr != nullptr);
}

void GravityComponent::update() {
	if (!onFloor_)
		entityTr->setVelY(entityTr->getVel().getY() + gravity / consts::FRAME_RATE);

	if (entityTr->getPos().getY() > 600) entityTr->setVelY(0);
}

void GravityComponent::reachedFloor() {
	if (entityTr->getVel().getY() > consts::FALLING_DMG_SPEED) std::cout << "OUCH, CAI DESDE MUY ALTO Y YOJHAN ES FEO";
	entityTr->setVelY(0);
	setOnFloor(true);
}