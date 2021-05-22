#include "KeyboardPlayerCtrl.h"
#include "../classes/player.h"
#include "../game/constant_variables.h"
#include "../components/box_collider.h"
#include "../classes/weapon_behaviour.h"
#include "../classes/physiognomy.h"
#include "../sdlutils/SoundManager.h"

KeyboardPlayerCtrl::KeyboardPlayerCtrl() {
	maxSpeed = consts::PLAYER_SPEED;
	jumpSpeed = consts::JUMP_SPEED;
	stairsSpeed = consts::STAIRS_SPEED;
	acceleration = consts::ACCELERATION;
	deceleration = consts::DECELERATION;
	cooldown = 0.0f;
	walking = false; climbing = false;
	tr_ = nullptr; rb_ = nullptr; darkArea = nullptr;

	speed = 0;
	left = xClicked = onLadder = onLadderTrigger = right = crouched = up = down = spaceDown = false;
};

void KeyboardPlayerCtrl::init() {
	rb_ = entity_->getComponent<RigidBody>();
	tr_ = entity_->getComponent<Transform>();
	assert(rb_ != nullptr && tr_ != nullptr);

	auto ent = entity_->getMngr()->addEntity();
	darkArea = ent->addComponent<Transform>(Vector2D(), consts::WINDOW_WIDTH * 2, consts::WINDOW_HEIGHT * 2);
	auto a = ent->addComponent<Image>(&sdlutils().images().at("dark"));

	darkArea->setPos(tr_->getPos() - Vector2D(consts::WINDOW_WIDTH, consts::WINDOW_HEIGHT));

	a->setAlpha(240);
	entity_->getMngr()->addRenderLayer<Dark>(ent);
}

void KeyboardPlayerCtrl::OnCollision(Entity* bc) {
	if (rb_->onFloor() && rb_->collisionVelocity.getY() > consts::FALLING_DMG_SPEED) {
		static_cast<Player*>(entity_)->getPhysiognomy()->addConcussionState();
		soundManager().playSFX("bonecrack");
	}
}

void KeyboardPlayerCtrl::OnTrigger(Entity* bc) {
	if (bc->hasGroup<Ladders_grp>()) {
		auto stairTr = bc->getComponent<Transform>();
		stairPosition = stairTr->getPos();
		stairSize = stairTr->getSize();
		onLadderTrigger = true;
	}
}

void KeyboardPlayerCtrl::update() {
	rb_->setGravity(consts::GRAVITY);

	if ((walking || climbing) && sdlutils().currRealTime() - 500 > cooldown) {
		if (walking) walking = false;
		else if (climbing) climbing = false;
		cooldown = sdlutils().currRealTime();
	}

	darkArea->setPos(tr_->getPos() - Vector2D(consts::WINDOW_WIDTH, consts::WINDOW_HEIGHT));

	if (!onLadder) {
		if (!crouched) {
			if (keystates[SDL_SCANCODE_D]) {
				speed += acceleration * consts::DELTA_TIME;
				if (speed > maxSpeed) speed = maxSpeed;
				//rb_->setVel(Vector2D(speed, rb_->getVel().getY()));
				right = true;
				if (tr_->getPos().getX() > stairPosition.getX() + stairSize.getX()) onLadderTrigger = false;
				if (!walking && rb_->onFloor()) {
					soundManager().playSFX("walk");
					walking = true;
					cooldown = sdlutils().currRealTime();
				}
			}
			else if (keystates[SDL_SCANCODE_A]) {
				speed -= acceleration * consts::DELTA_TIME;
				if (speed < -maxSpeed) speed = -maxSpeed;
				//rb_->setVel(Vector2D(-speed, rb_->getVel().getY()));
				left = true;
				if (tr_->getPos().getX() + tr_->getW() < stairPosition.getX()) onLadderTrigger = false;
				if (!walking && rb_->onFloor()) {
					soundManager().playSFX("walk");
					walking = true;
					cooldown = sdlutils().currRealTime();
				}
			}
			else {
				if (speed < -0.1f)
					speed += deceleration * consts::DELTA_TIME;
				else if (speed > 0.1f)
					speed -= deceleration * consts::DELTA_TIME;

				if (abs(speed) < .1f)
					speed = 0;
			}
			rb_->setVel(Vector2D(speed, rb_->getVel().getY()));

			if (onLadderTrigger && (keystates[SDL_SCANCODE_W] || keystates[SDL_SCANCODE_S])) {
				onLadder = true;
				tr_->setPos(Vector2D(stairPosition.getX(), tr_->getPos().getY()));
				soundManager().playSFX("climbsound");
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
				WeaponBehaviour* aux = static_cast<Player*>(entity_)->getWeapon();

				aux->getCurrentWeapon()->reload();
			}

			if (keystates[SDL_SCANCODE_X] && !xClicked) //Cambiar arma
			{
				WeaponBehaviour* aux = static_cast<Player*>(entity_)->getWeapon();
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
		if (keystates[SDL_SCANCODE_SPACE] && !spaceDown) { 
			onLadder = false; spaceDown = true;
		}
		else if (!keystates[SDL_SCANCODE_SPACE] && spaceDown) spaceDown = false;
		else {
			if (keystates[SDL_SCANCODE_W]) {
				rb_->setVel(Vector2D(0, -stairsSpeed));
				up = true;
				speed = 0;
				tr_->setPos(Vector2D(stairPosition.getX(), tr_->getPos().getY()));

				if (!climbing) {
					soundManager().playSFX("climbsound");
					climbing = true;
					cooldown = sdlutils().currRealTime();
				}

				if (tr_->getPos().getY() + tr_->getH() < stairPosition.getY()) {
					onLadderTrigger = false;
					onLadder = false;
					rb_->setVelY(-stairsSpeed * 2);
				}
			}
			else if (keystates[SDL_SCANCODE_S]) {
				rb_->setVel(Vector2D(0, stairsSpeed));
				down = true;
				speed = 0;
				tr_->setPos(Vector2D(stairPosition.getX(), tr_->getPos().getY()));
				if (!climbing) {
					soundManager().playSFX("climbsound");
					climbing = true;
					cooldown = sdlutils().currRealTime();
				}

				if (tr_->getPos().getY() > stairPosition.getY() + stairSize.getY()) {
					onLadderTrigger = false;
					onLadder = false;
				}
			}
			else {
				if (rb_->onFloor()) {
					onLadder = false;
				}
				rb_->setGravity(0);
				rb_->setVel(Vector2D(0, 0));
				up = down = false;
			}
		}

	}
	std::cout << speed << std::endl;
}

void KeyboardPlayerCtrl::resetSpeed() {
	rb_->setVel(Vector2D(0, rb_->getVel().getY()));
}

float KeyboardPlayerCtrl::getSpeed() {
	return speed;
}

float KeyboardPlayerCtrl::getMaxSpeed()
{
	return maxSpeed;
}

void KeyboardPlayerCtrl::setSpeed(float speed_) {
	speed = speed_;
}
void KeyboardPlayerCtrl::setMaxSpeed(float speed_) {
	maxSpeed = speed_;
}
void KeyboardPlayerCtrl::setJumpSpeed(float jumpSpeed_) {
	jumpSpeed = jumpSpeed_;
}