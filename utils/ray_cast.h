#ifndef RAYCAST_H_
#define RAYCAST_H_
#include "Vector2D.h"
#include "Collisions.h"
#include <array>
#include <limits>

class RayCast
{
private:
	Point2D origin = Point2D();
	Vector2D direction = Vector2D();
	Point2D pointOfImpact = NULL;
	double distance = -1.0;

	
	class Square
	{
	public:
		std::array<Point2D, 4> vertices; // 4 points, arranged anti-clockwise
		Point2D centre;

		Square() : vertices(std::array<Point2D, 4>()), centre(Point2D()) {};
		Square(Point2D p) {};

		Square(Point2D centre_, Point2D vertex0, Point2D vertex1): centre(centre_)
		{
			vertices[0] = vertex0;
			vertices[1] = vertex1;
			vertices[2] = centre + (centre - vertex0);
			vertices[3] = centre + (centre - vertex1);
		}
	};

private:
	static short int getClosestVertex(const Point2D& p, const Square& s)
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

public:
	RayCast(Point2D origin_, Vector2D direction_) {};
	
	template<typename ...rTs, typename ...sTs>
	static RayCast rayCastToSquare(rTs... rCastArgs, sTs... squareArgs)
	{
		RayCast rC = RayCast(rCastArgs);
		//Square s = Square(); // Square(squareArgs);
		Square s =  Square(squareArgs);

		Vector2D perp = Vector2D(rC.direction.getY(), -rC.direction.getX());

		Point2D closestPointInLine = Point2D();
		Vector2D::intersection(s.centre, perp, rC.origin, rC.direction, closestPointInLine);

		short int closestVertex = getClosestVertex(closestPointInLine, s);
		Vector2D closestEdgeDirection = s.vertices[closestVertex] - s.vertices[(closestVertex + 1) % 4];

		Vector2D::intersection(rC.origin, rC.direction, s.vertices[closestVertex], closestEdgeDirection, rC.pointOfImpact);
		
		if (Collisions::PointInRectangle(s.vertices[0], s.vertices[1], s.vertices[2], s.vertices[3], rC.pointOfImpact)) // if collision occurred
		{
			Point2D intersect = Point2D();
			double auxDistance = 0.0f;
			closestEdgeDirection = s.vertices[closestVertex] - s.vertices[(closestVertex - 1) % 4];

			Vector2D::intersection(rC.origin, rC.direction, s.vertices[closestVertex], closestEdgeDirection, intersect);

			if ((intersect - rC.origin).magnitude() > (rC.pointOfImpact - rC.origin).magnitude())
				rC.pointOfImpact = intersect;

			rC.distance = (rC.pointOfImpact - rC.origin).magnitude();
		}
		else // if there was no collision
		{
			rC.pointOfImpact = NULL;
			rC.distance = -1.0;
		}
	}
};

#endif