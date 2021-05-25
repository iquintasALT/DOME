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

class player_animation : public AnimationComponent {
private:
	const enum animations_name { idle = 0, walking, crouch, walking_arms, idle_arms, crouch_arms, climbing, dmg_idle, dmg_crouch, dmg_climb };
	Animation animations[10]{
	Animation(idle, 4),
	Animation(walking, 14, true, 1.25),
	Animation(crouch, 4),
	Animation(walking_arms, 14, true, 1.25),
	Animation(idle_arms, 4),
	Animation(crouch_arms, 4),
	Animation(climbing, 4, true, 1.75),
	Animation(dmg_idle, 1),
	Animation(dmg_crouch, 1),
	Animation(dmg_climb, 1)};

	Animation currentAnimation = animations[idle];
	float timer = 0;

	bool changeAnimations();
//-----------------------------------------------------------------------------
	Image* im_;
	Transform* tr_;
	RigidBody* rb;
	KeyboardPlayerCtrl* playerCtrl_;
	bool animStop;
	bool dmgReceived;
	float cooldown;

	ParticleSystem* walkDust;

public:
	player_animation();

	virtual void init();

	virtual ~player_animation();

	virtual void update();
	inline void setDmg(bool dmg) { dmgReceived = dmg; };
};