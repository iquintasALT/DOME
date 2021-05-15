#pragma once
#include "animation_component.h"
class WeaponAnimation :
    public AnimationComponent
{
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
	Animation(laser_windup_0, 8, false, 1 / consts::CHARGE_TIER1_TIMETOCHARGE),
	Animation(laser_windup_1, 8, false, 1 / consts::CHARGE_TIER2_TIMETOCHARGE),
	Animation(laser_windup_2, 8, false, 1 / consts::CHARGE_TIER3_TIMETOCHARGE),
	Animation(laser_sustaining_0, 4),
	Animation(laser_sustaining_1, 4),
	Animation(laser_sustaining_2, 4)
	};
};

