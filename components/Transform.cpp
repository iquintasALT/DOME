#include "Transform.h"

Transform::Transform() :
	pos_(), width_(), height_(), rotation_(), collisions_(nullptr) { }

Transform::Transform(Vector2D pos, float width, float height,
	float rotation) : pos_(pos), width_(width), height_(height), rotation_(rotation), collisions_(nullptr) { }

Transform:: ~Transform() { }

void Transform::init() {
	collisions_ = entity_->getComponent<PlayerCollisions>();
}