#pragma once

#include "../components/animation_component.h"
#include "../components/Image.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/checkML.h"
#include "../sdlutils/InputHandler.h"
#include "../game/constant_variables.h"
#include "../components/KeyboardPlayerCtrl.h"
#include "../components/rigid_body.h"
#include "../components/particleSystem.h"
#include <iostream>

class player_animation : public animation_component {
private:
	const enum animations_name { iddle = 0, walking, crouch, walking_arms, idle_arms, crouch_arms, climbing, climb_shoot };
	Animation animations[8]{
	Animation(iddle, 4),
	Animation(walking, 14),
	Animation(crouch, 4),
	Animation(walking_arms, 14),
	Animation(idle_arms, 4),
	Animation(crouch_arms, 4),
	Animation(climbing, 4),
	Animation(climb_shoot, 2)};

	Animation currentAnimation = animations[iddle];
	float timer = 0;

	bool changeAnimations();
//-----------------------------------------------------------------------------
	Image* im_;
	Transform* tr_;
	RigidBody* rb;
	KeyboardPlayerCtrl* ctrl;
	bool animStop;

	ParticleSystem* walkDust;

public:
	player_animation();

	virtual void init();

	virtual ~player_animation();

	virtual void update();
};