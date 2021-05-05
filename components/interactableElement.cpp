#include "interactableElement.h"
#include "../ecs/Manager.h"
#include "TextWithBackGround.h"
#include <iostream>
#include "../sdlutils/SDLUtils.h"
#include "../game/constant_variables.h"

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
	toolTip->getComponent<TextWithBackground>()->reset();
	toolTip->setActive(true);
}


void InteractableElement::CollisionExit() {
	toolTip->setActive(false);
}

void InteractableElement::Interact() {
}

void InteractableElement::init() {
	tr_ = entity_->getComponent<Transform>();
	entity_->getMngr()->AddInteractableElement(this);

	toolTip = entity_->getMngr()->addEntity();
	toolTip->addComponent<Transform>(Vector2D(consts::WINDOW_WIDTH / 2, consts::WINDOW_HEIGHT * 0.8f), consts::WINDOW_WIDTH, 10);
	toolTip->addComponent<TextWithBackground>(message_,
		sdlutils().fonts().at("ARIAL32"), build_sdlcolor(0xffffffff), nullptr, true, 100, true);
	entity_->getMngr()->addRenderLayer<Interface>(toolTip);
	toolTip->setActive(false);

	assert(tr_ != nullptr);
}