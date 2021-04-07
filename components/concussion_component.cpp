#include "concussion_component.h"
#include "../classes/player.h"
#include "KeyboardPlayerCtrl.h"
#include "../classes/physiognomy.h"

ConcussionComponent::~ConcussionComponent() {
	activateJump();
}

void ConcussionComponent::init() {
	kb = static_cast<Player*>(entity_)->getComponent<KeyboardPlayerCtrl>();
	assert(kb != nullptr);

	phys = static_cast<Player*>(entity_)->getPhysiognomy();

	time = sdlutils().currRealTime();
	cancelJump();
}

void ConcussionComponent::update() {
	if (sdlutils().currRealTime() > time + consts::CONTUSION_TIME_TO_END) {
		phys->removeState<ConcussionComponent>(this);
	}
}

void ConcussionComponent::cancelJump() {
	kb->setJumpSpeed(0.0f);
}
void ConcussionComponent::activateJump() {
	kb->setJumpSpeed(consts::JUMP_SPEED);
}
void ConcussionComponent::increaseTime(int time_) {
	time += time_;
}
