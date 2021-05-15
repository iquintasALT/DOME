#include "weapon_animation.h"


WeaponAnimation::WeaponAnimation() : tr_(nullptr), playerCtrl_(nullptr), im_(nullptr), rb(nullptr), animStop(false) { };

WeaponAnimation::~WeaponAnimation() {}

void WeaponAnimation::update() {
	timer += currentAnimation.animationSpeed();

	if (timer > 1 && !animStop) {
		currentAnimation.advanceFrame();
		timer = 0;
	}
}