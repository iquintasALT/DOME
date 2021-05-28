#include "player_animation.h"
#include "../classes/player.h"
#include "../classes/weapon_behaviour.h"

PlayerAnimation::PlayerAnimation() : tr_(nullptr), playerCtrl_(nullptr), im_(nullptr), rb(nullptr), walkDust(nullptr){
	animStop = false;
	dmgReceived = false;
	cooldown = 0.0f;
};

PlayerAnimation::~PlayerAnimation() {}

void PlayerAnimation::update() {
	if (changeAnimations()) {
		timer = 0; return;
	}
	timer += currentAnimation.animationSpeed();

	if (timer > 1 && !animStop) {
		currentAnimation.advanceFrame();
		timer = 0;
	}

	if (dmgReceived && sdlutils().currRealTime() - 200 > cooldown) {
		dmgReceived = false;
		cooldown = sdlutils().currRealTime();
	}
}

void PlayerAnimation::init() {
	currentAnimation.setImage(im_ = entity_->getComponent<Image>());

	for (Animation& anim : animations) {
		anim.setImage(im_);
	}

	tr_ = entity_->getComponent<Transform>();
	rb = entity_->getComponent<RigidBody>();
	playerCtrl_ = entity_->getComponent<KeyboardPlayerCtrl>();
	walkDust = entity_->getComponent<ParticleSystem>();
	walkDust->Stop();
	assert(tr_ != nullptr && im_ != nullptr && playerCtrl_ != nullptr && rb != nullptr && walkDust != nullptr);
}
bool debug = false;

bool PlayerAnimation::changeAnimations() {
	//std::cout << to_string((animations_name)currentAnimation.getCurrentFrame()) << endl;
	auto& mouse = ih().getMousePos();
	float mouseX = Camera::mainCamera->PointToWorldSpace(Vector2D(mouse.first, mouse.second)).getX();
	float playerX = tr_->getPos().getX() + tr_->getW() / 2;
	WeaponBehaviour* aux = static_cast<Player*>(entity_)->getWeapon();
	float x = rb->getVel().getX();

	float xdir = mouseX - playerX;
	if (aux->isActive()) {
		if (xdir < 0) im_->setFlip(SDL_FLIP_HORIZONTAL);
		else  im_->setFlip(SDL_FLIP_NONE);
	}
	else if (x != 0) {
			if (x < 0) im_->setFlip(SDL_FLIP_HORIZONTAL);
			else  im_->setFlip(SDL_FLIP_NONE);
	}

	if (dmgReceived) {
		if (currentAnimation == animations[dmg_climb]
			|| currentAnimation == animations[dmg_crouch]
			|| currentAnimation == animations[dmg_idle])
			return false;

		if (playerCtrl_->isCrouching()) {
			currentAnimation = animations[dmg_crouch];
		}
		else if (playerCtrl_->isClimbingLadder()) {
			walkDust->Stop();
			currentAnimation = animations[dmg_climb];
		}
		else {
			currentAnimation = animations[dmg_idle];
		}
		cooldown = sdlutils().currRealTime();
		currentAnimation.render();
		return true;
	}

	if (playerCtrl_->isCrouching() && !playerCtrl_->isClimbingLadder()) {
		if (aux->isActive()) {
			if (currentAnimation == animations[crouch])
				return false;
			currentAnimation = animations[crouch];
		}
		else {
			if (currentAnimation == animations[crouch_arms])
				return false;
			currentAnimation = animations[crouch_arms];
		}
		currentAnimation.render();
		walkDust->Stop();
		return true;
	}

	if (playerCtrl_->isClimbingLadder()) {
		walkDust->Stop();
		if (rb->getVel().getY() != 0) {
			animStop = false;
			if (currentAnimation == animations[climbing])
				return false;

			currentAnimation = animations[climbing];
			currentAnimation.render();
			return true;
		}
		else {
			animStop = true;
			return false;
		}
	}

	if (x == 0) {
		if (aux->isActive()) {
			if (currentAnimation == animations[idle])
				return false;
			currentAnimation = animations[idle];
			animStop = false;
		}
		else {
			if (currentAnimation == animations[idle_arms])
				return false;
			currentAnimation = animations[idle_arms];
			animStop = false;
		}
		currentAnimation.render();
		walkDust->Stop();
		return true;
	}
	
	if (aux->isActive()) {
		if (currentAnimation != animations[walking]) {
			currentAnimation = animations[walking];
			currentAnimation.render();
			walkDust->Play();
			return true;
		}
		return false;
	}
	else {
		if (currentAnimation != animations[walking_arms]) {
			currentAnimation = animations[walking_arms];
			currentAnimation.render();
			walkDust->Play();
			return true;
		}
		return false;
	}
	return false;
}