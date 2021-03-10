#pragma once
#include "../ecs/Entity.h"
#include "../utils/Vector2D.h"
class GameObject: public Entity
{
protected:
	Point2D position;
	Vector2D size;
public:
	Point2D getPosition() { return position; };
	Vector2D getSize() { return size; };
	void setPosition(Point2D newPosition) { position = newPosition; };
	void setSize(Vector2D newSize) { size = newSize; };
	void scale(float scale) {size = size * scale;};
	void update() {};
};

