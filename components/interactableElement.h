#pragma once

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../components/Transform.h"
#include <string>
#include "../utils/checkML.h"

using namespace std;

class InteractableElement: public Component
{
private:
	string message;
	Transform* transform;
	bool isColliding = false;

	virtual void CollisionEnter();
	virtual void CollisionExit();
	virtual void Collision();

public:
	InteractableElement(string msg);
	void init() override; 
	virtual void Interact();
	bool CheckCollision(Point2D playerPos);
};

