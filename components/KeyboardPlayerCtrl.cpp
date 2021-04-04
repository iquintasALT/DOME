#include "KeyboardPlayerCtrl.h"
#include "../classes/player.h"
#include "../classes/camera.h"

KeyboardPlayerCtrl::KeyboardPlayerCtrl() {
	speed = consts::PLAYER_SPEED;
	jumpSpeed = consts::JUMP_SPEED;
	entityTr = nullptr;
	gravity_ = nullptr;
	left = right = crouched = false;
};

void KeyboardPlayerCtrl::init() {
	entityTr = entity_->getComponent<Transform>();
	assert(entityTr != nullptr);

	gravity_ = entity_->getComponent<GravityComponent>();
	assert(entityTr != nullptr);

}

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

		if (keystates[SDL_SCANCODE_SPACE] && gravity_->onFloor()) {
 			entityTr->setVel(Vector2D(entityTr->getVel().getX(), -jumpSpeed));
			gravity_->setOnFloor(false);
		}

		if (keystates[SDL_SCANCODE_LCTRL] && entityTr->getVel().getY() == 0) {
			// Esta línea es solo para tema visual:
			entityTr->setPos(Vector2D(entityTr->getPos().getX(), entityTr->getPos().getY()));
			entityTr->setVel(Vector2D(0, 0));
			crouched = true;
		}

		//Test key for debugging
		if (keystates[SDL_SCANCODE_J]) {
			//dynamic_cast<Player*>(entity_)->equipWeapon(new WeaponBehaviour());
		}
	}
	else if (!keystates[SDL_SCANCODE_LCTRL]) {
		// Esta línea es para que se quede a la misma altura (no se hunda en el suelo)
		entityTr->setPos(Vector2D(entityTr->getPos().getX(), entityTr->getPos().getY()));
		crouched = false;
	}

	//Camera::mainCamera->FollowPlayer(entityTr->getPos());
}

void KeyboardPlayerCtrl::resetSpeed() {
	entityTr->setVel(Vector2D(0, entityTr->getVel().getY()));
}
float KeyboardPlayerCtrl::getSpeed() {
	return speed;
}
void KeyboardPlayerCtrl::setSpeed(float speed_) {
	speed = speed_;
}
void KeyboardPlayerCtrl::setJumpSpeed(float jumpSpeed_) {
	jumpSpeed = jumpSpeed_;
}