#include "Transform.h"

Transform::Transform() :
	pos_(), width_(), height_(), rotation_(){ }

Transform::Transform(Vector2D pos, float width, float height,
	float rotation) : pos_(pos), width_(width), height_(height), rotation_(rotation) { }

Transform:: ~Transform() { }
