#pragma once

#include "../ecs/Component.h"
#include "Image.h"
#include "../sdlutils/SDLUtils.h"

class player_animation : public Component {
public:
	player_animation() : im_(nullptr), tr_(nullptr) {
		frameX_ = 0; frameY_ = 0;
	};

	void init() {
		im_ = entity_->getComponent<Image>();
		tr_ = entity_->getComponent<Transform>();
		assert(im_ != nullptr && tr_ != nullptr);
	}

	virtual ~player_animation() {};

	void playerWalk() {
		if (frameX_ > 13) frameX_ = 0;

		frameY_ = 1;
		auto rect = im_->getSrc();
		int x = tr_->getVel().getX();
		if (x != 0) {
			if (x < 0)	im_->setFlip(SDL_FLIP_HORIZONTAL);
			else if (x > 0) im_->setFlip(SDL_FLIP_NONE);

			rect.x = rect.w * frameX_;
			rect.y = rect.h * frameY_;

			im_->setSrc(rect);
			frameX_++;
		}
		else {
			rect.x = 0;
			rect.y = 0;
			im_->setSrc(rect);
		}
	}

	void update() {

		if (sdlutils().currRealTime() >= frameTime + 1000/12) {
			frameTime = sdlutils().currRealTime();

			playerWalk();
			
		}
	}

private:
	Image* im_;
	Transform* tr_;
	int frameX_; int frameY_; 
	float frameTime = 0;
};