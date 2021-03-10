#include "KeyboardPlayerCtrl.h"

void KeyboardPlayerCtrl::update() {
	if (ih().isKeyDown(SDL_SCANCODE_D) && entityTr->getVel().getX() <= 0) {
		entityTr->setVel(Vector2D(speed, entityTr->getVel().getY()));
	}
	else if (ih().isKeyDown(SDL_SCANCODE_A) && entityTr->getVel().getX() >= 0) {
		entityTr->setVel(Vector2D(-speed, entityTr->getVel().getY()));
	}
	else if (ih().isKeyUp(SDL_SCANCODE_A) && ih().isKeyUp(SDL_SCANCODE_D)) {
		entityTr->setVel(Vector2D(0, entityTr->getVel().getY()));
	}
	else if (ih().isKeyDown(SDL_SCANCODE_SPACE) && entityTr->getVel().getY() == 0) {
		entityTr->setVel(Vector2D(entityTr->getVel().getX(), -speed));
	}
}
