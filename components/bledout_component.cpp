#include "bledout_component.h"
#include "../classes/player.h"
#include "../classes/physiognomy.h"
#include "../components/hunger_component.h"
#include "../sdlutils/SDLUtils.h"

void BledoutComponent::init() {
	accumulatedTime = sdlutils().currRealTime();
	phys = static_cast<Player*>(entity_)->getPhysiognomy();

	hunger = entity_->getComponent<HungerComponent>();
}

void BledoutComponent::update() {
	if (sdlutils().currRealTime() > accumulatedTime + hunger->calculateBledingSpeed()) {
		accumulatedTime = sdlutils().currRealTime();
		phys->getHealthComponents()->push_back(this);
	}
}
