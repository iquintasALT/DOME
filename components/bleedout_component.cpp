#include "bleedout_component.h"
#include "../classes/player.h"
#include "../classes/physiognomy.h"
#include "../components/hunger_component.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"

void BleedoutComponent::init() {
	accumulatedTime = sdlutils().currRealTime();
	phys = static_cast<Player*>(entity_)->getPhysiognomy();

	hunger = entity_->getComponent<HungerComponent>();
	assert(hunger != nullptr);
}

void BleedoutComponent::update() {
	if (sdlutils().currRealTime() > accumulatedTime + hunger->calculateBleedingSpeed()) {
		accumulatedTime = sdlutils().currRealTime();
		phys->addBleedState();
	}
}
