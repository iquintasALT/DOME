#include "player_animation.h"

Image* player_animation::Animation::image = nullptr;
int player_animation::Animation::width = 1;
int player_animation::Animation::height = 1;

player_animation::player_animation() : tr_(nullptr), ctrl(nullptr), im_(nullptr), rb(nullptr) {};

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
	Animation::setImage(im_ = entity_->getComponent<Image>());
	tr_ = entity_->getComponent<Transform>();
	rb = entity_->getComponent<RigidBody>();
	ctrl = entity_->getComponent<KeyboardPlayerCtrl>();

	assert(tr_ != nullptr && im_ != nullptr && ctrl != nullptr && rb != nullptr);
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

	//float x = tr_->getVel().getX();
	float x = rb->getVel().getX();
	if (x == 0) {
			if (currentAnimation == animations[iddle])
				return false;
		currentAnimation = animations[iddle];
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