#include "GravityComponent.h"

GravityComponent::GravityComponent() {
	gravity = consts::GRAVITY;
	onFloor_ = false;
	rb_ = nullptr;
}

void GravityComponent::init() {
	rb_ = entity_->getComponent<RigidBody>();
	assert(rb_ != nullptr);
}

void GravityComponent::applyGravity() {
	if (!onFloor_)
		rb_->setVelY(rb_->getVel().getY() + gravity / consts::FRAME_RATE);

	//if (entityTr->getPos().getY() > 600) entityTr->setVelY(0);
}

void GravityComponent::reachedFloor() {
	if (rb_->getVel().getY() > consts::FALLING_DMG_SPEED) std::cout << "OUCH, CAI DESDE MUY ALTO Y YOJHAN ES FEO";
	rb_->setVelY(0);
	setOnFloor(true);
}