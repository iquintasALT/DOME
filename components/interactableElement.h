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
	Entity* toolTip;
	bool isColliding = false;
	
	virtual void CollisionEnter();
	virtual void CollisionExit();
public:
	InteractableElement(string msg);
	virtual ~InteractableElement() {};
	void init() override; 
	virtual void Interact();
	bool CheckCollision(Point2D playerPos, float width, float height);
	bool CheckCollision(Transform* tr) { return CheckCollision(tr->getPos(), tr->getW(), tr->getH()); };
};

//interactableElement->addComponent<TextWithBackground>("Press E to open the loot",
//sdlutils().fonts().at("Orbitron32"), build_sdlcolor(0xffffffff), nullptr, false, 0, true);

