#include "rigid_body.h"

RigidBody::RigidBody() : vel_(Vector2D()), rotation_(0) { }

RigidBody::RigidBody(Vector2D vel, float rotation) : vel_(vel), rotation_(rotation) { }

RigidBody::~RigidBody() {};

void RigidBody::init() {
	tr_ = entity_->getComponent<Transform>();

	assert(tr_ != nullptr);
}

void RigidBody::update() {
	tr_->getPos() = tr_->getPos() + vel_;
}