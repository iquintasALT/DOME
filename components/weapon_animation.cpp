#include "weapon_animation.h"


WeaponAnimation::WeaponAnimation() : tr_(nullptr), im_(nullptr), rb(nullptr), animStop(false) { };

WeaponAnimation::~WeaponAnimation() {}

void WeaponAnimation::update() {
	timer += currentAnimation.animationSpeed();

	if (timer > 1 && !animStop) {
		currentAnimation.advanceFrame();
		timer = 0;
	}
}

void WeaponAnimation::init() {
	currentAnimation.setImage(im_ = entity_->getComponent<Image>());

	for (Animation& anim : animations) {
		anim.setImage(im_);
	}

	tr_ = entity_->getComponent<Transform>();
	rb = entity_->getComponent<RigidBody>();
	assert(tr_ != nullptr && im_ != nullptr && rb != nullptr);
}