#include "interactableElement.h"
#include "../ecs/Manager.h"
#include <iostream>

InteractableElement::InteractableElement(string msg) :message(msg), transform(nullptr) {}

bool InteractableElement::CheckCollision(Point2D pos, float width, float height) {
	bool inCollision = false;
	float x = pos.getX() + width / 2;
	float y = pos.getY() + height / 2;
	inCollision = x > transform->getPos().getX() &&
			      x < transform->getPos().getX() + transform->getW() &&
		          y > transform->getPos().getY() &&
		          y < transform->getPos().getY() + transform->getH();


	if (inCollision && !isColliding) CollisionEnter();
	if (!inCollision && isColliding) CollisionExit();


	isColliding = inCollision;
	return inCollision;
}


void InteractableElement::CollisionEnter() {
	std::cout << "Collision enter" << std::endl;
}


void InteractableElement::CollisionExit() {
	std::cout << "Collision exit" << std::endl;
}

void InteractableElement::Interact() {
	std::cout << message << std::endl;
}

void InteractableElement::Collision() {

}

void InteractableElement::init(){
	transform = entity_->getComponent<Transform>();
	entity_->getMngr()->AddInteractableElement(this);

	assert(transform != nullptr);
}