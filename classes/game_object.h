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
	inline GameObject(Manager* mngr_) : Entity(mngr_) {}
	inline Point2D getPosition() { return position; };
	inline Vector2D getSize() { return size; };
	inline void setPosition(Point2D newPosition) { position = newPosition; };
	inline void setSize(Vector2D newSize) { size = newSize; };
	inline void scale(float scale) { size = size * scale; };
	//virtual void update() {};
};

