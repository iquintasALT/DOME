#include "interactableElement.h"
#include "../ecs/Manager.h"
#include <iostream>
bool InteractableElement::CheckCollision(Point2D pos) {
	bool inCollision = false;

	inCollision = pos.getX() > transform->getPos().getX() &&
		pos.getX() < transform->getPos().getX() + transform->getW() &&
		pos.getY() > transform->getPos().getY() &&
		pos.getY() < transform->getPos().getY() + transform->getH();


	if (inCollision && !isColliding) CollisionEnter();
	if (!inCollision && isColliding) CollisionExit();

	if (inCollision) std::cout << message;

	return inCollision;
}


void InteractableElement::CollisionEnter() {
	std::cout << "Collision enter";
}


void InteractableElement::CollisionExit() {
	std::cout << "Collision exit";
}

void InteractableElement::Interact() {
	std::cout << "Interact OWO";
}


void InteractableElement::init(){
	transform = entity_->getComponent<Transform>();
	entity_->getMngr()->AddInteractableElement(this);
}