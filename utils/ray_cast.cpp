#include "ray_cast.h"
#include "../components/Transform.h"


void RayCast::rayCastToSquare(Transform* transform)
{
	Point2D centre = transform->getPos() + transform->getSize() / 2;
	Point2D rightCorner = Point2D(transform->getPos().getX() + transform->getW(), transform->getPos().getY());
	rayCastToSquare(centre, transform->getPos(), rightCorner);
}

void RayCast::rayCastToSquare(Entity* entity)
{
	if (entity->hasComponent<Transform>())
		rayCastToSquare(entity->getComponent<Transform>());
}