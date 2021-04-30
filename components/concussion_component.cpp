#include "concussion_component.h"
#include "../classes/player.h"
#include "KeyboardPlayerCtrl.h"
#include "../classes/physiognomy.h"
#include "../sdlutils/SDLUtils.h"

ConcussionComponent::~ConcussionComponent() {
	activateJump();
}

void ConcussionComponent::init() {
	kb = static_cast<Player*>(entity_)->getComponent<KeyboardPlayerCtrl>();
	assert(kb != nullptr);

	phys = static_cast<Player*>(entity_)->getPhysiognomy();

	frameIndex = 1;

	time = sdlutils().currRealTime();
	cancelJump();
}

void ConcussionComponent::update() {
	if (sdlutils().currRealTime() > time + consts::CONTUSION_TIME) {
		phys->removeConcussionState();
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
