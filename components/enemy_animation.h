#pragma once

#include "../components/animation_component.h"
#include "../components/image.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/checkML.h"
#include "../sdlutils/InputHandler.h"
#include "../game/constant_variables.h"
#include "../components/rigid_body.h"
#include <iostream>

class EnemyAnimation : public AnimationComponent {
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
	Transform* playerTr_;
	RigidBody* rb;
	bool dmgReceived;
	bool isAttacking;
	float cooldown;
public:
	EnemyAnimation();

	virtual void init();

	virtual ~EnemyAnimation();

	virtual void update();
	
	inline bool isDamaged() { return dmgReceived; };
	inline void setDamaged(bool dmg) { dmgReceived = dmg; };
	inline bool isAttack() { return isAttacking; };
	inline void setAttack(bool attack) { isAttacking = attack; };
};

class FlyingEnemyAnimation : public AnimationComponent {
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
	FlyingEnemyAnimation();

	virtual void init();

	virtual ~FlyingEnemyAnimation();

	virtual void update();

	inline bool isDamaged() { return dmgReceived; };
	inline void setDamaged(bool dmg) { dmgReceived = dmg; };
	inline bool isAttack() { return isAttacking; };
	inline void setAttack(bool attack) { isAttacking = attack; };
};