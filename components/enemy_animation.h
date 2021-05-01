#pragma once

#include "../components/animation_component.h"
#include "../components/Image.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/checkML.h"
#include "../sdlutils/InputHandler.h"
#include "../game/constant_variables.h"
#include "../components/rigid_body.h"
#include <iostream>

class enemy_animation : public animation_component {
private:
	const enum animations_name { idle = 0, walking };
	Animation animations[2]{
	Animation(idle, 4),
	Animation(walking, 9) };

	Animation currentAnimation = animations[idle];
	float timer = 0;

	bool changeAnimations();
	//-----------------------------------------------------------------------------
	Image* im_;
	Transform* tr_;
	RigidBody* rb;

public:
	enemy_animation();

	virtual void init();

	virtual ~enemy_animation();

	virtual void update();
};

class flying_enemy_animation : public animation_component {
private:
	const enum animations_name { idle = 0, attack};
	Animation animations[2]{
	Animation(idle, 4),
	Animation(attack, 4)};

	Animation currentAnimation = animations[idle];
	float timer = 0;

	bool changeAnimations();
	//-----------------------------------------------------------------------------
	Image* im_;
	Transform* tr_;
	RigidBody* rb;

public:
	flying_enemy_animation();

	virtual void init();

	virtual ~flying_enemy_animation();

	virtual void update();
};