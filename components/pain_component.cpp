#include "pain_component.h"
#include "../classes/physiognomy.h"
#include "concussion_component.h"
#include "intoxication_component.h"
#include "../ecs/Manager.h"

void PainComponent::init() {
	phys = static_cast<Player*>(entity_)->getPhysiognomy();
	time = sdlutils().currRealTime();
	weapon = entity_->getComponent<WeaponBehaviour>();
}
void PainComponent::increaseTime() {
	for (auto b : *phys->getHealthComponents()) {
		if (dynamic_cast<ConcussionComponent*>(b) != nullptr) {
			static_cast<ConcussionComponent*>(b)->increaseTime(consts::TIME_TO_INCREASE_CONTUSION);
		}
		else if (dynamic_cast<IntoxicationComponent*>(b) != nullptr) {
			static_cast<IntoxicationComponent*>(b)->increaseTime(consts::TIME_TO_INCREASE_INTOXICATION);
		}
	}
}
void PainComponent::update() {
	if (sdlutils().currRealTime() > time + consts::TIME_PER_NEWSUMOFTIME) {
		time = sdlutils().currRealTime();
		increaseTime();
	}
}
void PainComponent::newState() {

}
