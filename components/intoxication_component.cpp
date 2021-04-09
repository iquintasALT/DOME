#include "intoxication_component.h"
#include "../classes/player.h"
#include "KeyboardPlayerCtrl.h"
#include "../classes/physiognomy.h"
#include "../components/hunger_component.h"

void IntoxicationComponent::init() {
	time = sdlutils().currRealTime();
	phys = static_cast<Player*>(entity_)->getPhysiognomy();
	hunger = entity_->getComponent<HungerComponent>();

	assert(entity_ != nullptr);
}
void IntoxicationComponent::increaseTime(int time_) {
	time += time_;
}
void IntoxicationComponent::update() {
	auto actTime = sdlutils().currRealTime();
	if (actTime > time + consts::INTOXICATION_TIME_TO_END) {
		//phys->removeState<IntoxicationComponent>(this);
	}
	else if (actTime > timeToApplyHunger + consts::TIME_TO_DECREASE_HUNGER) {
		timeToApplyHunger = actTime;
		hunger->decreaseHunger(consts::HUNGER_TO_DECREASE);
		cout << hunger->getHunger();
	}
}
void IntoxicationComponent::newState() {

}