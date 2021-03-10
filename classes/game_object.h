#pragma once
#include "../ecs/Entity.h"
#include "../utils/Vector2D.h"
class GameObject: public Entity
{
protected:
	Point2D position;
	Vector2D size;
public:
	Point2D getPosition();
	Vector2D getSize();
	void setPosition();
	void setSize();
	void setScale();
	void update();
};

