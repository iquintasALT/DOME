#include "enemy_animation.h"


enemy_animation::enemy_animation() : tr_(nullptr), im_(nullptr), rb(nullptr) {};

enemy_animation::~enemy_animation() {}

void enemy_animation::update() {
	if (changeAnimations()) {
		timer = 0; return;
	}
	timer += currentAnimation.animationSpeed();

	if (timer > 1) {
		currentAnimation.advanceFrame();
		timer = 0;
	}
}

void enemy_animation::init() {
	currentAnimation.setImage(im_ = entity_->getComponent<Image>());

	for (Animation& anim : animations) {
		anim.setImage(im_);
	}

	tr_ = entity_->getComponent<Transform>();
	rb = entity_->getComponent<RigidBody>();
	assert(tr_ != nullptr && im_ != nullptr && rb != nullptr);
}

bool enemy_animation::changeAnimations() {

	float x = rb->getVel().getX();
	if (x == 0) {
		if (currentAnimation == animations[idle])
			return false;
		currentAnimation = animations[idle];
		currentAnimation.render();
		return true;
	}

	if (x < 0) im_->setFlip(SDL_FLIP_HORIZONTAL);
	else  im_->setFlip(SDL_FLIP_NONE);

	if (currentAnimation != animations[walking]) {
		currentAnimation = animations[walking];
		return true;
	}
	return false;
}

//-----------------------------------------------------------------------------------------------------------

flying_enemy_animation::flying_enemy_animation() : tr_(nullptr), im_(nullptr), rb(nullptr) {};

flying_enemy_animation::~flying_enemy_animation() {}

void flying_enemy_animation::init() {
	currentAnimation.setImage(im_ = entity_->getComponent<Image>());

	for (Animation& anim : animations) {
		anim.setImage(im_);
	}

	tr_ = entity_->getComponent<Transform>();
	rb = entity_->getComponent<RigidBody>();
	assert(tr_ != nullptr && im_ != nullptr && rb != nullptr);
}

void flying_enemy_animation::update() {
	if (changeAnimations()) {
		timer = 0; return;
	}
	timer += currentAnimation.animationSpeed();

	if (timer > 1) {
		currentAnimation.advanceFrame();
		timer = 0;
	}
}

bool flying_enemy_animation::changeAnimations() {

	float x = rb->getVel().getX();

	if (x < 0) im_->setFlip(SDL_FLIP_HORIZONTAL);
	else  im_->setFlip(SDL_FLIP_NONE);

	return false;
}