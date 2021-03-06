#pragma once
#include "animation_component.h"
class Image;
class Transform;
class Rigidbody;
class KeyBoardPlayerCtrl;
class WeaponAnimation :
    public AnimationComponent
{
private:

	Image* im_;
	Transform* tr_;

	const enum animations_name { regular_gun_0, regular_gun_1, regular_gun_2, ricochet_0, ricochet_1, ricochet_2, 
		laser_uncharged_0, laser_uncharged_1, laser_uncharged_2, laser_windup_0, laser_windup_1, laser_windup_2,
		laser_sustaining_0, laser_sustaining_1, laser_sustaining_2};

	Animation animations[15]{
	Animation(regular_gun_0, 1),
	Animation(regular_gun_1, 1),
	Animation(regular_gun_2, 1),
	Animation(ricochet_0, 1),
	Animation(ricochet_1, 1),
	Animation(ricochet_2, 1),
	Animation(laser_uncharged_0, 1),
	Animation(laser_uncharged_1, 1),
	Animation(laser_uncharged_2, 1),
	Animation(laser_windup_0, 8, false, 1 / consts::WEAPON_FIRERATES[6]),
	Animation(laser_windup_1, 8, false, 1 / consts::WEAPON_FIRERATES[7]),
	Animation(laser_windup_2, 8, false, 1 / consts::WEAPON_FIRERATES[8]),
	Animation(laser_sustaining_0, 4),
	Animation(laser_sustaining_1, 4),
	Animation(laser_sustaining_2, 4)
	};

	Animation currentAnimation = animations[regular_gun_0];
	float timer = 0;

public:
	WeaponAnimation();
	~WeaponAnimation();

	void setAnimation(int a) { currentAnimation = animations[a]; currentAnimation.advanceFrame(); };

	virtual void init();

	virtual void update();
};

