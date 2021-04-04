#include "KeyboardPlayerCtrl.h"
#include "../classes/player.h"
#include "../classes/camera.h"

KeyboardPlayerCtrl::KeyboardPlayerCtrl() {
	speed = consts::PLAYER_SPEED;
	rb_ = nullptr;
	left = right = crouched = false;
};

void KeyboardPlayerCtrl::init() {
	rb_ = entity_->getComponent<RigidBody>();
	assert(rb_ != nullptr);
}

void KeyboardPlayerCtrl::update() {
	if (!crouched) {
		if (keystates[SDL_SCANCODE_D]) {
			rb_->setVel(Vector2D(speed, rb_->getVel().getY()));
			right = true;
		}
		else if (keystates[SDL_SCANCODE_A]) {
			rb_->setVel(Vector2D(-speed, rb_->getVel().getY()));
			left = true;
		}
		else {
			rb_->setVel(Vector2D(0, rb_->getVel().getY()));
		}

		if (keystates[SDL_SCANCODE_SPACE] && rb_->onFloor()) {
 			rb_->setVel(Vector2D(rb_->getVel().getX(), -speed));
			rb_->setOnFloor(false);
		}

		if (keystates[SDL_SCANCODE_LCTRL] && rb_->getVel().getY() == 0) {
			// Esta línea es solo para tema visual:
			tr_->setPos(Vector2D(tr_->getPos().getX(), tr_->getPos().getY()));
			rb_->setVel(Vector2D(0, 0));
			crouched = true;
		}

		//Test key for debugging
		if (keystates[SDL_SCANCODE_J]) {
			//dynamic_cast<Player*>(entity_)->equipWeapon(new WeaponBehaviour());
		}
	}
	else if (!keystates[SDL_SCANCODE_LCTRL]) {
		// Esta línea es para que se quede a la misma altura (no se hunda en el suelo)
		tr_->setPos(Vector2D(tr_->getPos().getX(), tr_->getPos().getY()));
		crouched = false;
	}

	//Camera::mainCamera->FollowPlayer(entityTr->getPos());
}

void KeyboardPlayerCtrl::resetSpeed() {
	rb_->setVel(Vector2D(0, rb_->getVel().getY()));
}

float KeyboardPlayerCtrl::getSpeed() {
	return speed;
}

void KeyboardPlayerCtrl::setSpeed(float speed_) {
	speed = speed_;
}