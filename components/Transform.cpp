#include "Transform.h"

Transform::Transform() :
	pos_(), vel_(), width_(), height_(), rotation_(), collisions_(nullptr) { }

Transform::Transform(Vector2D pos, Vector2D vel, float width, float height,
	float rotation) : pos_(pos), vel_(vel), width_(width), height_(height), rotation_(rotation), collisions_(nullptr) { }

Transform:: ~Transform() { }

void Transform::init() {
	collisions_ = entity_->getComponent<PlayerCollisions>();
}

void Transform::update() {
	pos_ = pos_ + vel_;
}