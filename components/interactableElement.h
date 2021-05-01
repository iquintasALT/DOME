#pragma once

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include <string>
#include "../utils/checkML.h"

using namespace std;

class TextWithBackground;
class InteractableElement: public Component
{
protected:
	string message_;
	Transform* tr_;
	// Tooltip text if required
	TextWithBackground* toolTip_;
	bool isColliding = false;

	virtual void CollisionEnter();
	virtual void CollisionExit();
	virtual void Collision();
public:
	InteractableElement(string msg);
	virtual ~InteractableElement() {};
	void init() override; 
	virtual void Interact();
	bool CheckCollision(Point2D playerPos, float width, float height);
	bool CheckCollision(Transform* tr) { return CheckCollision(tr->getPos(), tr->getW(), tr->getH()); };
};

