#include "ray_cast.h"
#include "../components/Transform.h"
#include "../ecs/Entity.h"

RayCast::RayCast(Point2D origin, Transform* tr): origin_(origin)
{
	direction_ = Point2D(tr->getPos() + tr->getSize() / 2.0) - origin_;
	rayCastToSquare(tr);
}

void RayCast::rayCastToSquare(Vector2D centre, Vector2D vertex0, Vector2D vertex1)
{
	//Create square from points given
	Square s = Square(centre, vertex0, vertex1);

	//Calculate which vertex from square is closest to ray origin
	short int closestVertex = getClosestVertex(origin_, s);
	//Choose one of the two sides that converge at closestVertex
	Vector2D closestEdgeDirection1 = s.vertices[closestVertex] - s.vertices[(closestVertex + 1) % 4], closestEdgeDirection2;
	if (closestVertex == 0)
		closestEdgeDirection2 = s.vertices[closestVertex] - s.vertices[3];
	else
		closestEdgeDirection2 = s.vertices[closestVertex] - s.vertices[(closestVertex - 1) % 4];

	//Calculate intersection between raycast line and each edge that connects to the vertex closest to ray origin
	Point2D pointOfImpact1, pointOfImpact2;
	bool col1 = (Vector2D::intersection(origin_, direction_, s.vertices[closestVertex], closestEdgeDirection1, pointOfImpact1)),
		col2 = Vector2D::intersection(origin_, direction_, s.vertices[closestVertex], closestEdgeDirection2, pointOfImpact2);

	//Move both points of impact ever so slightly closer to square center, to account for floating point imprecision
	pointOfImpact1 = pointOfImpact1 + Vector2D(centre - pointOfImpact1) * 0.001;
	pointOfImpact2 = pointOfImpact2 + Vector2D(centre - pointOfImpact2) * 0.001;

	//See if either or both points of collision are within rectangle bounds
	col1 &= Collisions::PointInRectangle(s.vertices[0], s.vertices[1], s.vertices[2], s.vertices[3], pointOfImpact1);
	col2 &= Collisions::PointInRectangle(s.vertices[0], s.vertices[1], s.vertices[2], s.vertices[3], pointOfImpact2);

	//If neither collision was registered, the ray does not intersect the rectangle
	if (!col1 && !col2)
	{
		pointOfImpact_ = Point2D();
		distance_ = -1.0;
	}
	else
	{
		//If both collisions registered, save the one nearest to ray origin
		if (col1 && col2)
		{
			if ((pointOfImpact1 - origin_).magnitude() > (pointOfImpact2 - origin_).magnitude())
				pointOfImpact_ = pointOfImpact1;
			else
				pointOfImpact_ = pointOfImpact2;
		}
		//Otherwise, save the only collision point
		else if (col1)
			pointOfImpact_ = pointOfImpact1;
		else
			pointOfImpact_ = pointOfImpact2;
		distance_ = (pointOfImpact_ - origin_).magnitude();
	}
}

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

short int RayCast::getClosestVertex(const Point2D& p, const Square& s)
{
	short int closest = 0;
	float distance = std::numeric_limits<float>::max();
	for (short int i = 0; i < 4; i++)
	{
		if ((s.vertices[i] - p).magnitude() < distance)
		{
			closest = i;
			distance = (s.vertices[i] - p).magnitude();
		}
	}
	return closest;
}

bool RayCast::isGrounded(Transform* tr)
{
	RayCast rC = RayCast(tr->getPos() + Vector2D(tr->getW() / 2, tr->getH()), Vector2D(0.0, -1.0));
	rC.distanceToGroup<Wall_grp>(tr->getEntity()->getMngr());
	return rC.distance_ != -1.0 && rC.distance_ < 0.2;
}