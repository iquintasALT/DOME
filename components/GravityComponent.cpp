#include "GravityComponent.h"

void GravityComponent::update() {
	entityTr = entity_->getComponent<Transform>();
	if (entityTr != nullptr) {
		if (entityTr->getPos().getY() < 600 - entityTr->getH())
			entityTr->setVel(Vector2D(entityTr->getVel().getX(), entityTr->getVel().getY() + gravity / 60));
		else {
			entityTr->setVel(Vector2D(entityTr->getVel().getX(), 0));
		}
	}
}