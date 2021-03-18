#include "player_animation.h"

void player_animation::playerWalk() {
	auto rect = im_->getSrc();

	int x = tr_->getVel().getX();

	if (x != 0) {
		frameY_ = 1; frameDivision = 12;
		if (frameX_ > 13) frameX_ = 0;

		if (x < 0)	im_->setFlip(SDL_FLIP_HORIZONTAL);
		else if (x > 0) im_->setFlip(SDL_FLIP_NONE);
	}
	else {
		frameY_ = 0; frameDivision = 3;
		if (frameX_ > 3) frameX_ = 0;
	}

	rect.x = rect.w * frameX_;
	rect.y = rect.h * frameY_;
	frameX_++;
	im_->setSrc(rect);
}

void player_animation::update() {
	if (sdlutils().currRealTime() >= frameTime + 1000 / frameDivision) {
		frameTime = sdlutils().currRealTime();
		playerWalk();
	}
}

void player_animation::init() {
	im_ = entity_->getComponent<Image>();
	tr_ = entity_->getComponent<Transform>();
	assert(im_ != nullptr && tr_ != nullptr);
}