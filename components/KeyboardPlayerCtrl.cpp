#include "KeyboardPlayerCtrl.h"

void KeyboardPlayerCtrl::update() {
	entityTr = entity_->getComponent<Transform>();
	if (entityTr != nullptr) {
		if (ih().isKeyDown(SDL_SCANCODE_D))
			entityTr->setVel(Vector2D(speed, entityTr->getVel().getY()));
		else if (ih().isKeyDown(SDL_SCANCODE_A)) {
			entityTr->setVel(Vector2D(-speed, entityTr->getVel().getY()));
		}
		else if (entityTr->getVel().getX() > 0) {
			entityTr->setVel(Vector2D(entityTr->getVel().getX() - 0.35, entityTr->getVel().getY()));
		}
		else if (entityTr->getVel().getX() < 0) {
			entityTr->setVel(Vector2D(entityTr->getVel().getX() + 0.35, entityTr->getVel().getY()));
		}
		if (ih().isKeyDown(SDL_SCANCODE_SPACE)) {
			entityTr->setVel(Vector2D(entityTr->getVel().getX(), -speed));
		}
	}
}