#include "interactable_element.h"
#include "../ecs/Manager.h"
#include "text_with_background.h"
#include <iostream>
#include "../sdlutils/SDLUtils.h"
#include "../game/constant_variables.h"
#include "particle_system.h"
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
		sdlutils().fonts().at("OrbitronRegular"), build_sdlcolor(0xffffffff), nullptr, true, 100, true);
	entity_->getMngr()->addRenderLayer<Interface>(toolTip);
	toolTip->setActive(false);

	assert(tr_ != nullptr);

	auto pEntity = entity_->getMngr()->addEntity();
	entity_->getMngr()->addRenderLayer<Loot>(pEntity);
	pEntity->addComponent<Transform>(tr_->getPos() + Vector2D(tr_->getW(), tr_->getH()) / 2);
	auto particles = pEntity->addComponent<ParticleSystem>(
		&sdlutils().images().at("brillibrilli"), 1, 1, 0, 0);

	//Rate over time
	particles->emitting = true;
	particles->rateOverTime = .8;
	particles->destroyAfterTime = false;
	particles->lifeTime = 3;

	//Direction
	particles->dir = Vector2D(0, 1);
	particles->speed = .05;
	particles->distanceToOrigin = (tr_->getH() > tr_->getW() ? tr_->getH() : tr_->getW()) / 2;
	particles->insideCircle = true;
	particles->angleDispersion = 360;
	particles->gravity = true;
	particles->gravityValue = 0.05;
	particles->initialRotation = 0;
	particles->randomRotation = true;
	particles->rotationSpeed = .2;
	//size
	particles->sizeOverTime = true;
	particles->particleScale = 1;
	particles->sizeCurve = ParticleSystem::Function(-4, 4, 0);

	//burst
	particles->burst = false;
}