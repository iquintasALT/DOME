#include "hypothermia_component.h"
#include "../sdlutils/SDLUtils.h"
#include "../game/constant_variables.h"
#include "../classes/physiognomy.h"

void HypothermiaComponent::init() {
	time = sdlutils().currRealTime();
	phys = static_cast<Player*>(entity_)->getPhysiognomy();
}

void HypothermiaComponent::update() {
	if (sdlutils().currRealTime() > time + consts::HYPOTHERMIA_TIME) {
		phys->die();
	}
	hypothermia = (float)(100 * sdlutils().currRealTime() / (consts::HYPOTHERMIA_TIME))/100;
}
