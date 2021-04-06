#include "intoxication_component.h"
#include "../classes/player.h"
#include "KeyboardPlayerCtrl.h"
#include "../classes/physiognomy.h"

void IntoxicationComponent::init() {
	time = sdlutils().currRealTime();
	phys = static_cast<Player*>(entity_)->getPhysiognomy();
}
void IntoxicationComponent::increaseTime(int time_) {
	time += time_;
}
void IntoxicationComponent::update() {
	if (sdlutils().currRealTime() > time + consts::INTOXICATION_TIME_TO_END) {
		phys->removeState<IntoxicationComponent>(this);
	}
}