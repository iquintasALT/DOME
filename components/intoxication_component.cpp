#include "intoxication_component.h"
#include "../classes/player.h"
#include "keyboard_player_ctrl.h"
#include "../classes/physiognomy.h"
#include "../components/hunger_component.h"

void IntoxicationComponent::init() {
	time = sdlutils().currRealTime();
	phys = static_cast<Player*>(entity_)->getPhysiognomy();

	frameIndex = 0;

	hunger = entity_->getComponent<HungerComponent>();

	assert(entity_ != nullptr);
}
void IntoxicationComponent::increaseTime(int time_) {
	time += time_;
}
void IntoxicationComponent::update() {
	auto actTime = sdlutils().currRealTime();
	if (actTime > time + consts::INTOXICATION_TIME) {
		phys->removeIntoxicationState();
	}
	else if (actTime > timeToApplyHunger + consts::TIME_TO_DECREASE_HUNGER) {
		timeToApplyHunger = actTime;
		hunger->decreaseHunger(consts::HUNGER_TO_DECREASE);
	}
}
