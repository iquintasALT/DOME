#pragma once

#include "../components/animation_component.h"
#include "../components/Image.h"
#include "../sdlutils/SDLUtils.h"
#include "../game/checkML.h"
#include "../sdlutils/InputHandler.h"
#include "../game/constant_variables.h"
#include "../components/KeyboardPlayerCtrl.h"

#include <iostream>

class player_animation : public animation_component {
public:
	player_animation() : tr_(nullptr), ctrl(nullptr), im_(nullptr) {};

	virtual void init();

	virtual ~player_animation() {};

	virtual void update();

private:
	const enum animations_name { iddle = 0, walking, crouch };
	Animation animations[3]{
	Animation(iddle, 3),
	Animation(walking, 14),
	Animation(crouch, 3) };

	Animation currentAnimation = animations[iddle];
	float timer = 0;

	bool changeAnimations();
//-----------------------------------------------------------------------------
	Image* im_;
	Transform* tr_;
	KeyboardPlayerCtrl* ctrl;
};