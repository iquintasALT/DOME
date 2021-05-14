#include "enemy_animation.h"


EnemyAnimation::EnemyAnimation() : tr_(nullptr), im_(nullptr), rb(nullptr) {
	isAttacking = false;
	dmgReceived = false;
};

EnemyAnimation::~EnemyAnimation() {}

void EnemyAnimation::update() {
	if (changeAnimations()) {
		timer = 0; return;
	}
	timer += currentAnimation.animationSpeed();

	if (timer > 1) {
		currentAnimation.advanceFrame();
		timer = 0;
	}

	if (isAttacking && sdlutils().currRealTime() - 400 > cooldown) {
		isAttacking = false;
		cooldown = sdlutils().currRealTime();
	}
}

void EnemyAnimation::init() {
	currentAnimation.setImage(im_ = entity_->getComponent<Image>());

	for (Animation& anim : animations) {
		anim.setImage(im_);
	}

	tr_ = entity_->getComponent<Transform>();
	rb = entity_->getComponent<RigidBody>();
	playerTr_ = entity_->getMngr()->getHandler<Player_hdlr>()->getComponent<Transform>();
	assert(tr_ != nullptr && im_ != nullptr && rb != nullptr && playerTr_ != nullptr);
}

bool EnemyAnimation::changeAnimations() {

	float x = rb->getVel().getX();
	float playerX = playerTr_->getPos().getX();
	if (x < 0) im_->setFlip(SDL_FLIP_HORIZONTAL);
	else if (x > 0)  im_->setFlip(SDL_FLIP_NONE);
	else {
		if (playerX < tr_->getPos().getX()) im_->setFlip(SDL_FLIP_HORIZONTAL);
		else  im_->setFlip(SDL_FLIP_NONE);
	}
	
	if (isAttacking) {
		if (playerX < tr_->getPos().getX()) im_->setFlip(SDL_FLIP_HORIZONTAL);
		else  im_->setFlip(SDL_FLIP_NONE);

		if (currentAnimation == animations[attack])
			return false;
		currentAnimation = animations[attack];
		currentAnimation.render();
		cooldown = sdlutils().currRealTime();
		return true;
	}

	if (dmgReceived) {
		dmgReceived = false;
		if (currentAnimation == animations[dmg])
			return false;
		currentAnimation = animations[dmg];
		currentAnimation.render();
		return true;
	}

	if (x == 0) {
		if (currentAnimation == animations[idle])
			return false;
		currentAnimation = animations[idle];
		return true;
	}

	if (currentAnimation != animations[walking]) {
		currentAnimation = animations[walking];
		return true;
	}
	return false;
}

//-----------------------------------------------------------------------------------------------------------

FlyingEnemyAnimation::FlyingEnemyAnimation() : tr_(nullptr), im_(nullptr), rb(nullptr) {
	isAttacking = false;
	dmgReceived = false;
};

FlyingEnemyAnimation::~FlyingEnemyAnimation() {}

void FlyingEnemyAnimation::init() {
	currentAnimation.setImage(im_ = entity_->getComponent<Image>());

	for (Animation& anim : animations) {
		anim.setImage(im_);
	}

	tr_ = entity_->getComponent<Transform>();
	rb = entity_->getComponent<RigidBody>();
	assert(tr_ != nullptr && im_ != nullptr && rb != nullptr);
}

void FlyingEnemyAnimation::update() {
	if (changeAnimations()) {
		timer = 0; return;
	}
	timer += currentAnimation.animationSpeed();

	if (timer > 1) {
		currentAnimation.advanceFrame();
		timer = 0;
	}

	if (isAttacking && sdlutils().currRealTime() - 400 > cooldown) {
		isAttacking = false;
		cooldown = sdlutils().currRealTime();
	}
}

bool FlyingEnemyAnimation::changeAnimations() {

	float x = rb->getVel().getX();

	if (x >= 1) im_->setFlip(SDL_FLIP_HORIZONTAL);
	else  im_->setFlip(SDL_FLIP_NONE);

	if (isAttacking) {
		if (currentAnimation == animations[attack])
			return false;
		currentAnimation = animations[attack];
		currentAnimation.render();
		cooldown = sdlutils().currRealTime();
		return true;
	}

	if (dmgReceived) {
		dmgReceived = false;
		if (currentAnimation == animations[dmg])
			return false;
		currentAnimation = animations[dmg];
		currentAnimation.render();
		return true;
	}
	else
	{
	if (currentAnimation == animations[idle]) return false;
		currentAnimation = animations[idle];
		return true;
	}

	return false;
}