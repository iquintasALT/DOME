#pragma once
#include "../ecs/Entity.h"
#include "../utils/Vector2D.h"
#include "../game/checkML.h"

class GameObject : public Entity
{
protected:
	Point2D position = Point2D();
	Vector2D size = Vector2D();
public:
	GameObject(Manager* mngr_) : Entity(mngr_){}
	Point2D getPosition() { return position; };
	Vector2D getSize() { return size; };
	void setPosition(Point2D newPosition) { position = newPosition; };
	void setSize(Vector2D newSize) { size = newSize; };
	void scale(float scale) { size = size * scale; };
	virtual void update() {};
};

