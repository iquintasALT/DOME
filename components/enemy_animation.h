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
	const enum animations_name { idle = 0, walking, dmg, attack };
	Animation animations[4]{
	Animation(idle, 4),
	Animation(walking, 9),
	Animation(dmg, 3),
	Animation(attack, 3, true, 2)};

	Animation currentAnimation = animations[idle];
	float timer = 0;

	bool changeAnimations();
	//-----------------------------------------------------------------------------
	Image* im_;
	Transform* tr_;
	RigidBody* rb;
	bool dmgReceived;
	bool isAttacking;
	float cooldown;
public:
	enemy_animation();

	virtual void init();

	virtual ~enemy_animation();

	virtual void update();
	
	inline bool isDamaged() { return dmgReceived; };
	inline void setDamaged(bool dmg) { dmgReceived = dmg; };
	inline bool isAttack() { return isAttacking; };
	inline void setAttack(bool attack) { isAttacking = attack; };
};

class flying_enemy_animation : public animation_component {
private:
	const enum animations_name { idle = 0, attack, dmg};
	Animation animations[3]{
	Animation(idle, 4),
	Animation(attack, 4, true, 2),
	Animation(dmg, 3)};

	Animation currentAnimation = animations[idle];
	float timer = 0;

	bool changeAnimations();
	//-----------------------------------------------------------------------------
	Image* im_;
	Transform* tr_;
	RigidBody* rb;
	bool dmgReceived;
	bool isAttacking;
	float cooldown;

public:
	flying_enemy_animation();

	virtual void init();

	virtual ~flying_enemy_animation();

	virtual void update();

	inline bool isDamaged() { return dmgReceived; };
	inline void setDamaged(bool dmg) { dmgReceived = dmg; };
	inline bool isAttack() { return isAttacking; };
	inline void setAttack(bool attack) { isAttacking = attack; };
};