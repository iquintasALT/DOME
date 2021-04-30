#include "hypothermia_component.h"
#include "../sdlutils/SDLUtils.h"
#include "../game/constant_variables.h"
#include "../classes/physiognomy.h"

void HypothermiaComponent::init() {
	time = sdlutils().currRealTime();
	phys = static_cast<Player*>(entity_)->getPhysiognomy();
	frameIndex = 3;
	frost = &sdlutils().images().at("frost");
}

void HypothermiaComponent::update() {
	if (sdlutils().currRealTime() > time + consts::HYPOTHERMIA_TIME) {
		phys->die();
	}
	hypothermia = (float)(100 * sdlutils().currRealTime() / (consts::HYPOTHERMIA_TIME))/100;
}

void HypothermiaComponent::render() {
	frost->setAlpha(hypothermia * 255);
	frost->render(build_sdlrect(0, 0, sdlutils().width(), sdlutils().height()));
}
