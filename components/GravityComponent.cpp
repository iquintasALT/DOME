#include "GravityComponent.h"

void GravityComponent::update() {
	if (entityTr->getPos().getY() + entityTr->getVel().getY() < 600 - entityTr->getH())
		entityTr->setVel(Vector2D(entityTr->getVel().getX(), entityTr->getVel().getY() + gravity / consts::FRAME_RATE));
	else {
		entityTr->setVel(Vector2D(entityTr->getVel().getX(), 0));
	}
}