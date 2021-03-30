#include "ray_cast.h"
#include "../components/Transform.h"

void RayCast::rayCastToSquare(Vector2D centre, Vector2D vertex0, Vector2D vertex1)
{
	//Create square from points given
	Square s = Square(centre, vertex0, vertex1);
	//Calculate perpendicular direction vector to raycast direction
	Vector2D perp = Vector2D(direction.getY(), -direction.getX());

	//Calculate which vertex from square is closest to ray origin
	short int closestVertex = getClosestVertex(origin, s);
	//Choose one of the two sides that converge at closestVertex
	Vector2D closestEdgeDirection1 = s.vertices[closestVertex] - s.vertices[(closestVertex + 1) % 4];
	Vector2D closestEdgeDirection2 = s.vertices[closestVertex] - s.vertices[(closestVertex - 1) % 4];

	//Calculate intersection between raycast line and each edge that connects to the vertex closest to ray origin
	Point2D pointOfImpact1, pointOfImpact2;
	bool col1 = Vector2D::intersection(origin, direction, s.vertices[closestVertex], closestEdgeDirection1, pointOfImpact1), 
		col2 = Vector2D::intersection(origin, direction, s.vertices[closestVertex], closestEdgeDirection2, pointOfImpact2);
	if (col1 && col2)
	{
		if ((pointOfImpact1 - origin).magnitude() > (pointOfImpact2 - origin).magnitude())
			pointOfImpact = pointOfImpact1;
		else
			pointOfImpact = pointOfImpact2;

		distance = (pointOfImpact - origin).magnitude();
	}
	else if (col1)
	{
		pointOfImpact = pointOfImpact1;
		distance = (pointOfImpact - origin).magnitude();
	}
	else if (col2)
	{
		pointOfImpact = pointOfImpact2;
		distance = (pointOfImpact - origin).magnitude();
	}
	else
	{
		pointOfImpact = Point2D();
		distance = -1.0;
	}
	/*
	if (Collisions::PointInRectangle(s.vertices[0], s.vertices[1], s.vertices[2], s.vertices[3], pointOfImpact)) // if collision occurred
	{
		//Repeat necessary calculations for other eligible side
		Point2D intersect = Point2D();
		double auxDistance = 0.0f;
		closestEdgeDirection = s.vertices[closestVertex] - s.vertices[(closestVertex - 1) % 4];

		Vector2D::intersection(origin, direction, s.vertices[closestVertex], closestEdgeDirection, intersect);

		//Compare both sides to see which is closer
		if ((intersect - origin).magnitude() > (pointOfImpact - origin).magnitude())
			pointOfImpact = intersect;

		distance = (pointOfImpact - origin).magnitude();
	}
	else // if there was no collision
	{
		pointOfImpact = Point2D();
		distance = -1.0;
	}*/
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