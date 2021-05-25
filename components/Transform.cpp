#include "Transform.h"

Transform::Transform() :
	pos_(), width_(), height_(), rotation_(){ }

Transform::Transform(Vector2D pos, float width, float height,
	float rotation) : pos_(pos), width_(width), height_(height), rotation_(rotation) { }

Transform:: ~Transform() { }

Vector2D Transform::getCenterPos() {
	Vector2D centerPos = pos_;
	centerPos.setX(centerPos.getX() + width_ / 2);
	centerPos.setY(centerPos.getY() + height_ / 2);
	return centerPos;
}

void Transform::setCenterPos(Vector2D pos) {
	pos_ = pos;
	pos_.setX(pos_.getX() - width_ / 2);
	pos_.setY(pos_.getY() - height_ / 2);
} 
