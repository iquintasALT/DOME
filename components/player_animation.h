#pragma once

#include "../ecs/Component.h"
#include "Image.h"
#include "../sdlutils/SDLUtils.h"

class player_animation : public Component {
public:
	player_animation() : im_(nullptr), tr_(nullptr) {
		frameX_ = 0; frameY_ = 0;
	};

	virtual void init();

	virtual ~player_animation() {};

	void playerWalk();

	virtual void update();

private:
	Image* im_;
	Transform* tr_;
	int frameX_; int frameY_; 
	float frameTime = 0;
};