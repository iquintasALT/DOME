#include "contusion_component.h"
#include "../classes/player.h"
#include "KeyboardPlayerCtrl.h"
#include "../classes/physiognomy.h"

ContusionComponent::~ContusionComponent() {
	activateJump();
}

void ContusionComponent::init() {
	kb = static_cast<Player*>(entity_)->getComponent<KeyboardPlayerCtrl>();
	assert(kb != nullptr);

	phys = static_cast<Player*>(entity_)->getPhysiognomy();

	time = sdlutils().currRealTime();
	cancelJump();
}

void ContusionComponent::update() {
	if (sdlutils().currRealTime() > time + consts::CONTUSION_TIME_TO_END) {
		phys->removeState<ContusionComponent>(this);
	}
}

void ContusionComponent::cancelJump() {
	kb->setJumpSpeed(0.0f);
}
void ContusionComponent::activateJump() {
	kb->setJumpSpeed(consts::JUMP_SPEED);
}
void ContusionComponent::increaseTime(int time_) {
	time += time_;
}
