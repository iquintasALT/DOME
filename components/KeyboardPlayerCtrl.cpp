#include "KeyboardPlayerCtrl.h"
#include "../classes/player.h"

void KeyboardPlayerCtrl::update() {
	if (!crouched) {
		if (keystates[SDL_SCANCODE_D]) {
			entityTr->setVel(Vector2D(speed, entityTr->getVel().getY()));
			right = true;
		}
		else if (keystates[SDL_SCANCODE_A]) {
			entityTr->setVel(Vector2D(-speed, entityTr->getVel().getY()));
			left = true;
		}
		else {
			entityTr->setVel(Vector2D(0, entityTr->getVel().getY()));
		}

		if (keystates[SDL_SCANCODE_SPACE] && entityTr->getVel().getY() == 0) {
			entityTr->setVel(Vector2D(entityTr->getVel().getX(), -speed));
		}

		if (keystates[SDL_SCANCODE_LCTRL] && entityTr->getVel().getY() == 0) {
			// Esta línea es solo para tema visual:
			entityTr->setPos(Vector2D(entityTr->getPos().getX(), entityTr->getPos().getY() + entityTr->getH()/2));
			entityTr->setH(entityTr->getH() / 2);
			entityTr->setVel(Vector2D(0, 0));
			crouched = true;
		}

		//Test key for debugging
		if (keystates[SDL_SCANCODE_J]) {
			//dynamic_cast<Player*>(entity_)->equipWeapon(new WeaponBehaviour());
		}
	}
	else if (crouched && !keystates[SDL_SCANCODE_LCTRL]) {
		// Esta línea es para que se quede a la misma altura (no se hunda en el suelo)
		entityTr->setPos(Vector2D(entityTr->getPos().getX(), entityTr->getPos().getY() - entityTr->getH()));
		entityTr->setH(entityTr->getH() * 2);
		crouched = false;
	}
}

void KeyboardPlayerCtrl::resetSpeed() {
	entityTr->setVel(Vector2D(0, entityTr->getVel().getY()));
}