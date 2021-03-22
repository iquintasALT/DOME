#pragma once

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../components/Transform.h"
#include <string>
#include "../game/checkML.h"

class InteractableElement: public Component
{
private:
	std::string message;
	Transform* transform;
	bool isColliding = false;

	virtual void CollisionEnter();
	virtual void CollisionExit();
	virtual void Collision();

public:
	InteractableElement(std::string msg) :message(msg), transform(nullptr){};
	void init() override; 
	virtual void Interact();
	bool CheckCollision(Point2D playerPos);
};

