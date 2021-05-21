#include "hypothermia_component.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/SoundManager.h"
#include "../game/constant_variables.h"
#include "../classes/physiognomy.h"
#include "../classes/lose_scene.h"

void HypothermiaComponent::init() {
	phys = static_cast<Player*>(entity_)->getPhysiognomy();
	frameIndex = 3;
	frost = &sdlutils().images().at("frost");
	time = sdlutils().currRealTime();
	soundManager().playSFX("freeze");
}

void HypothermiaComponent::update() {
	hypothermia = (float)(100 * (sdlutils().currRealTime()-time) / (consts::HYPOTHERMIA_TIME)) / 100;
	if (hypothermia >= 1) phys->die(WAYSTODIE::COLD);
}

void HypothermiaComponent::render() {
	frost->setAlpha(hypothermia * 255);
	frost->render(build_sdlrect(0, 0, sdlutils().width(), sdlutils().height()));
}
