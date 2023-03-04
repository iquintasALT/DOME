#include "bleedout_component.h"
#include "../classes/player.h"
#include "../classes/physiognomy.h"
#include "../components/hunger_component.h"
#include "../game/constant_variables.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"

void BleedoutComponent::init() {
	accumulatedTime = sdlutils().currRealTime();
	phys = static_cast<Player*>(entity_)->getPhysiognomy();

	frameIndex = 6;
	renderPriority = -2;
	percentage = 0.0;

	hunger = entity_->getComponent<HungerComponent>();
	assert(hunger != nullptr);
}

void BleedoutComponent::update() {
	/*
	float fillAmount = accumulatedTime + hunger->bleedoutSpeed() / sdlutils().currRealTime() * 8;
	int fillAmount = hunger->bleedoutSpeed() / 8;
	if (fillAmount > 1.0) {
		accumulatedTime = sdlutils().currRealTime();
		phys->addBleedout();
	}*/

	/*
	int bleedTime = hunger->bleedoutSpeed();
	if (sdlutils().currRealTime() > accumulatedTime + bleedTime)
	{
		accumulatedTime = sdlutils().currRealTime();
		if (++frameIndex >= 13){
			phys->addBleedout();
			frameIndex = 6;
		}
	}*/
	if (percentage < 100.0)
	{
		float addPercentage; // percentage of bleed meter that fills this frame
		addPercentage = consts::DELTA_TIME * consts::BLOODLOSS_PER_SECOND_BASE * hunger->bleedoutSpeed();
		percentage += addPercentage;

		frameIndex = 6 + (7.0 * percentage / 100.0);
		if (percentage >= 100.0)
		{
			phys->increaseBloodloss();
			percentage = 0.0;
		}
	}
}

