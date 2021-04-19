#include "player_animation.h"


player_animation::player_animation() : tr_(nullptr), ctrl(nullptr), im_(nullptr), rb(nullptr), walkDust(nullptr){};

player_animation::~player_animation() {}

void player_animation::update() {
	if (changeAnimations()) {
		timer = 0; return;
	}
	timer += currentAnimation.animationSpeed();

	if (timer > 1) {
		currentAnimation.advanceFrame();
		timer = 0;
	}
}

void player_animation::init() {
	currentAnimation.setImage(im_ = entity_->getComponent<Image>());

	for (Animation& anim : animations) {
		anim.setImage(im_);
	}

	tr_ = entity_->getComponent<Transform>();
	rb = entity_->getComponent<RigidBody>();
	ctrl = entity_->getComponent<KeyboardPlayerCtrl>();
	walkDust = entity_->getComponent<ParticleSystem>();
	walkDust->Stop();
	assert(tr_ != nullptr && im_ != nullptr && ctrl != nullptr && rb != nullptr && walkDust != nullptr);
}
bool debug = false;

bool player_animation::changeAnimations() {
	if (ctrl->isCrouching()) {
		if (currentAnimation == animations[crouch])
			return false;

		currentAnimation = animations[crouch];
		currentAnimation.render();
		return true;
	}

	float mouseX = ih().getMousePos().first;
	float playerX = tr_->getPos().getX() + tr_->getW() / 2;

	float x = rb->getVel().getX();
	float xdir = mouseX - playerX;

	if (xdir < 0) im_->setFlip(SDL_FLIP_HORIZONTAL);
	else  im_->setFlip(SDL_FLIP_NONE);

	if (x == 0) {
		if (currentAnimation == animations[iddle])
			return false;
		currentAnimation = animations[iddle];
		currentAnimation.render();
		walkDust->Stop();
		return true;
	}
	
	if (currentAnimation != animations[walking]) {
		currentAnimation = animations[walking];
		walkDust->Play();
		return true;
	}
	return false;
}