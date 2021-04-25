#include "interactableElement.h"
#include "../ecs/Manager.h"
#include "TextWithBackGround.h"
#include <iostream>

InteractableElement::InteractableElement(string msg) : message_(msg), tr_(nullptr) {}

bool InteractableElement::CheckCollision(Point2D pos, float width, float height) {
	bool inCollision = false;
	float x = pos.getX() + width / 2;
	float y = pos.getY() + height / 2;
	inCollision = x > tr_->getPos().getX() &&
			      x < tr_->getPos().getX() + tr_->getW() &&
		          y > tr_->getPos().getY() &&
		          y < tr_->getPos().getY() + tr_->getH();


	if (inCollision && !isColliding) CollisionEnter();
	if (!inCollision && isColliding) CollisionExit();

	isColliding = inCollision;
	return inCollision;
}


void InteractableElement::CollisionEnter() {
	std::cout << "Collision enter" << std::endl;
	if (toolTip_ != nullptr)
		toolTip_->enabled = true;
}


void InteractableElement::CollisionExit() {
	std::cout << "Collision exit" << std::endl;
	if (toolTip_ != nullptr)
		toolTip_->enabled = false;
}

void InteractableElement::Interact() {
	std::cout << message_ << std::endl;
}

void InteractableElement::Collision() {

}

void InteractableElement::init(){
	tr_ = entity_->getComponent<Transform>();
	entity_->getMngr()->AddInteractableElement(this);
	toolTip_ = entity_->getComponent<TextWithBackground>();
	if (toolTip_ != nullptr)
		toolTip_->enabled = false;
	assert(tr_ != nullptr);
}