#include "KeyboardPlayerCtrl.h"
#include "../classes/player.h"
#include "../game/constant_variables.h"
#include "../components/box_collider.h"
#include "../classes/weapon_behaviour.h"

KeyboardPlayerCtrl::KeyboardPlayerCtrl() {
	speed = consts::PLAYER_SPEED;
	jumpSpeed = consts::JUMP_SPEED;
	stairsSpeed = consts::STAIRS_SPEED;
	tr_ = nullptr;
	rb_ = nullptr;
	
	left = xClicked = inStair = inStairTrigger = right = crouched = up = down =  false;
};

void KeyboardPlayerCtrl::init() {
	rb_ = entity_->getComponent<RigidBody>();
	tr_ = entity_->getComponent<Transform>();
	assert(rb_ != nullptr && tr_ != nullptr);
}

void KeyboardPlayerCtrl::OnCollision(Entity* bc) {
	if (rb_->onFloor() && rb_->collisionVelocity.getY() > consts::FALLING_DMG_SPEED)
		std::cout << "OUCH, QUE DOLOR, TENGA USTED MÁS CUIDADO JUGADOR";
}

void KeyboardPlayerCtrl::OnTrigger(Entity* bc) {
	if (bc->hasGroup<Ladders_grp>()) {
		auto stairTr = bc->getComponent<Transform>();
		stairPosition = stairTr->getPos();
		stairSize = stairTr->getSize();
		inStairTrigger = true;
	}
}

void KeyboardPlayerCtrl::update() {
	rb_->setGravity(consts::GRAVITY);
	if (!inStair) {
		if (!crouched) {
			if (keystates[SDL_SCANCODE_D]) {
				rb_->setVel(Vector2D(speed, rb_->getVel().getY()));
				right = true;
				if (tr_->getPos().getX() > stairPosition.getX() + stairSize.getX()) inStairTrigger = false;
			}
			else if (keystates[SDL_SCANCODE_A]) {
				rb_->setVel(Vector2D(-speed, rb_->getVel().getY()));
				left = true;
				if (tr_->getPos().getX() + tr_->getW() < stairPosition.getX()) inStairTrigger = false;
			}
			else {
				rb_->setVel(Vector2D(0, rb_->getVel().getY()));
			}
			if (inStairTrigger && (keystates[SDL_SCANCODE_W] || keystates[SDL_SCANCODE_S])) {
				inStair = true;
				tr_->setPos(Vector2D(stairPosition.getX(), tr_->getPos().getY()));
			}

			if (keystates[SDL_SCANCODE_SPACE] && rb_->onFloor()) {
				rb_->setVel(Vector2D(rb_->getVel().getX(), -jumpSpeed));
				//rb_->setOnFloor(false);
			}

			if (keystates[SDL_SCANCODE_LCTRL] && rb_->getVel().getY() == 0) {
				// Esta l�nea es solo para tema visual:
				tr_->setPos(Vector2D(tr_->getPos().getX(), tr_->getPos().getY()));
				rb_->setVel(Vector2D(0, 0));
				crouched = true;
			}

			if (keystates[SDL_SCANCODE_R]) //Recargar balas
			{
				WeaponBehaviour* aux = static_cast<Player*>(entity_)->getCurrentWeapon();

				aux->getWeaponMovement()->recharger();
			}

			if (keystates[SDL_SCANCODE_X] && !xClicked) //Cambiar arma
			{
				WeaponBehaviour* aux = static_cast<Player*>(entity_)->getCurrentWeapon();
				aux->changeWeapon();
				xClicked = true;
			}
			else if (!keystates[SDL_SCANCODE_X] && xClicked)
			{
				xClicked = false;
			}
		}
		else if (!keystates[SDL_SCANCODE_LCTRL]) {
			// Esta l�nea es para que se quede a la misma altura (no se hunda en el suelo)
			tr_->setPos(Vector2D(tr_->getPos().getX(), tr_->getPos().getY()));
			crouched = false;
		}
	}
	else {
		if (keystates[SDL_SCANCODE_SPACE]) inStair = false;
		else {
			if (keystates[SDL_SCANCODE_W]) {
				rb_->setVel(Vector2D(0, -stairsSpeed));
				up = true;
				tr_->setPos(Vector2D(stairPosition.getX(), tr_->getPos().getY()));
				if (tr_->getPos().getY() + tr_->getH() < stairPosition.getY()) {
					inStairTrigger = false;
					inStair = false;
				}
			}
			else if (keystates[SDL_SCANCODE_S]) {
				rb_->setVel(Vector2D(0, stairsSpeed));
				down = true;
				tr_->setPos(Vector2D(stairPosition.getX(), tr_->getPos().getY()));
				if (tr_->getPos().getY() > stairPosition.getY() + stairSize.getY()) {
					inStairTrigger = false;
					inStair = false;
				}
			}
			else {
				if (rb_->onFloor()) inStair = false;
				rb_->setGravity(0);
				rb_->setVel(Vector2D(0, 0));
				up = down = false;
			}
		}
		
	}

	//Camera::mainCamera->FollowPlayer(tr_->getPos());
	//Camera::mainCamera->Lerp(tr_->getPos());
	//Camera::mainCamera->LerpWithBounds(tr_->getPos());
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
void KeyboardPlayerCtrl::setJumpSpeed(float jumpSpeed_) {
	jumpSpeed = jumpSpeed_;
}