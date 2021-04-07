#ifndef RAYCAST_H_
#define RAYCAST_H_
#include "Vector2D.h"
#include "Collisions.h"
#include <array>
#include <limits>
#include "../game/checkML.h"
#include "../ecs/Entity.h"

class Transform;
class Entity;

class RayCast
{
private:
	Point2D origin = Point2D();
	Vector2D direction = Vector2D();
	Point2D pointOfImpact = Point2D();
	double distance = -1.0;

	
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

private:
	static short int getClosestVertex(const Point2D& p, const Square& s);

public:
	RayCast(Point2D origin_, Vector2D direction_) : origin(origin_), direction(direction_) {};

	double getDistance() { return distance; };

	Point2D getPointOfImpact() { return pointOfImpact; };
	
	bool hasCollision(float maxRange = std::numeric_limits<float>::max()) { return distance >= 0.0 && distance < maxRange; };

	void rayCastToSquare(Vector2D centre, Vector2D vertex0, Vector2D vertex1);

	void rayCastToSquare(Transform* transform);

	void rayCastToSquare(Entity* entity);

	/// Calculates minimum distance in a specified direction to any and all entities with transforms that belong to a certain group.
	/// Makes modifications to RayCast to display point of nearest collision and distance, which it returns
	/// If no collision is detected, distance will be -1.0
	template <typename Group>
	double distanceToGroup(Entity* entity)
	{
		auto entities = entity->getMngr()->getEntities();
		RayCast aux = RayCast(*this);
		for (Entity* e : entities)
		{
			if (e->hasGroup<Group>() && e->hasComponent<Transform>())
			{
				aux.rayCastToSquare(e->getComponent<Transform>());
				if (aux.distance != -1.0 && aux.distance < distance)
					*this = RayCast(aux);
			}
		}
		return distance;
	}

	// Returns true if transform is less than 0.2 above an object of group Wall_grp
	bool isGrounded(Transform* tr);
};

#endif