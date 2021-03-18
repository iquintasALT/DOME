#ifndef RAYCAST_H_
#define RAYCAST_H_
#include "Vector2D.h"
#include "Collisions.h"
#include <array>
#include <limits>

class RayCast
{
private:
	Point2D origin;
	Vector2D direction;
	class Square
	{
	public:
		std::array<Point2D, 4> vertices; // 4 points, arranged anti-clockwise
		Point2D centre;

		Square() : vertices(std::array<Point2D, 4>()), centre(Point2D()) {};
		Square(Point2D centre_, Point2D vertex0, Point2D vertex1): centre(centre_)
		{
			vertices[0] = vertex0;
			vertices[1] = vertex1;
			vertices[2] = centre + (centre - vertex0);
			vertices[3] = centre + (centre - vertex1);
		}
	};
public:
	RayCast(Point2D origin_, Vector2D direction_) : origin (origin_), direction (direction_) {};
	
	template<typename ...rTs, typename ...sTs>
	static bool rayCastCollidesWithSquare(rTs... rCastArgs, sTs... squareArgs)
	{
		RayCast rC = RayCast(rCastArgs);
		Square s = Square(squareArgs);

		Vector2D perp = Vector2D(rC.direction.getY(), -rC.direction.getX());

		Point2D closestPointInLine = Point2D();
		Vector2D::intersection(s, perp, rC.origin, rC.direction, closestPointInLine);

		short int closestVertex = getClosestVertex(closestPointInLine, s);
		Vector2D closestEdgeDirection = s.vertices[closestVertex] - s.vertices[(closestVertex + 1) % 4];

		Point2D intersect = Point2D();
		return (Vector2D::intersection(rC.origin, rC.direction, s.vertices[closestVertex], closestEdgeDirection, intersect)
			&& Collisions::PointInRectangle(s.vertices[0], s.vertices[1], s.vertices[2], s.vertices[3], intersect);
	}

	//TO DO
	Point2D getRayCastToSquareCollision();

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
};

#endif