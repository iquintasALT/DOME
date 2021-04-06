#include "rigid_body.h"

RigidBody::RigidBody(Vector2D vel, float rotation, bool gravity) : tr_(nullptr), vel_(vel), rotation_(rotation), 
			grActive_(gravity), onFloor_(false), gravity(consts::GRAVITY) { }

RigidBody::~RigidBody() {};

void RigidBody::init() {
	tr_ = entity_->getComponent<Transform>();

	assert(tr_ != nullptr);
}

void RigidBody::update() {
	tr_->getPos() = tr_->getPos() + vel_;
	if(grActive_) applyGravity();
}

void RigidBody::applyGravity() {
	if (!onFloor_)
		setVelY(vel_.getY() + gravity / consts::FRAME_RATE);

	//if (entityTr->getPos().getY() > 600) entityTr->setVelY(0);
}

void RigidBody::reachedFloor() {
	if (vel_.getY() > consts::FALLING_DMG_SPEED) std::cout << "OUCH, CAI DESDE MUY ALTO Y YOJHAN ES FEO";
	setVelY(0);
	setOnFloor(true);
}