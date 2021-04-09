#pragma once

#include "../components/animation_component.h"
#include "../components/Image.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/checkML.h"
#include "../sdlutils/InputHandler.h"
#include "../game/constant_variables.h"
#include "../components/KeyboardPlayerCtrl.h"
#include "../components/rigid_body.h"
#include <iostream>

class player_animation : public animation_component {
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
	RigidBody* rb;
	KeyboardPlayerCtrl* ctrl;

public:
	player_animation();

	virtual void init();

	virtual ~player_animation();

	virtual void update();
};