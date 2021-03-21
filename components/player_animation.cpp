#include "player_animation.h"

Image* player_animation::Animation::image = nullptr;
int player_animation::Animation::width = 1;
int player_animation::Animation::height = 1;

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
		if (ih().isKeyDown(SDL_SCANCODE_LCTRL)) {
			frameY_ = 2;
		}
		else
		{
			frameY_ = 0;
		}

		frameDivision = 3;
		if (frameX_ > 3) frameX_ = 0;
	}

	rect.x = rect.w * frameX_;
	rect.y = rect.h * frameY_;
	frameX_++;
	im_->setSrc(rect);
}

//
//void player_animation::update() {
//	if (sdlutils().currRealTime() >= frameTime + 1000 / frameDivision) {
//		frameTime = sdlutils().currRealTime();
//		//playerWalk();
//	}
//	playerWalk();
//}

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
	ctrl = entity_->getComponent<KeyboardPlayerCtrl>();

	assert(tr_ != nullptr && im_ != nullptr);
}
bool debug = false;

bool player_animation::changeAnimations() {
	/*if (ctrl->isCrouching()) {
		if (currentAnimation == animations[crouch])
			return false;

		currentAnimation = animations[crouch];
		currentAnimation.render();
		return true;
	}*/

	float x = tr_->getVel().getX();
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