#include "KeyboardPlayerCtrl.h"

void KeyboardPlayerCtrl::update() {

	if (entityTr->getVel().getX() <= 0 && ih().isKeyDown(SDL_SCANCODE_D)) {
		entityTr->setVel(Vector2D(speed, entityTr->getVel().getY()));
	}
	else if (entityTr->getVel().getX() >= 0 && ih().isKeyDown(SDL_SCANCODE_A)) {
		entityTr->setVel(Vector2D(-speed, entityTr->getVel().getY()));
	}
	else if (ih().isKeyUp(SDL_SCANCODE_A) && ih().isKeyUp(SDL_SCANCODE_D)) {
		entityTr->setVel(Vector2D(0, entityTr->getVel().getY()));
	}
	else if (entityTr->getVel().getY() == 0 && ih().isKeyDown(SDL_SCANCODE_SPACE)) {
		entityTr->setVel(Vector2D(entityTr->getVel().getX(), -speed));
	}
}
