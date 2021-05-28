#include "bleedout_component.h"
#include "../classes/player.h"
#include "../classes/physiognomy.h"
#include "../components/hunger_component.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"

void BleedoutComponent::init() {
	accumulatedTime = sdlutils().currRealTime();
	phys = static_cast<Player*>(entity_)->getPhysiognomy();

	frameIndex = 6;

	hunger = entity_->getComponent<HungerComponent>();
	assert(hunger != nullptr);
}

void BleedoutComponent::update() {
	/*
	float fillAmount = accumulatedTime + hunger->calculateBleedingSpeed() / sdlutils().currRealTime() * 8;
	int fillAmount = hunger->calculateBleedingSpeed() / 8;
	if (fillAmount > 1.0) {
		accumulatedTime = sdlutils().currRealTime();
		phys->addBleedState();
	}*/

	int bleedTime = hunger->calculateBleedingSpeed();
	if (sdlutils().currRealTime() > accumulatedTime + bleedTime)
	{
		accumulatedTime = sdlutils().currRealTime();
		if (++frameIndex >= 13){
			phys->addBleedState();
			frameIndex = 6;
		}
	}
}

