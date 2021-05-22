#include "tiredness_component.h"
#include "../sdlutils/InputHandler.h"

TirednessComponent::TirednessComponent() : tiredness(1.0f), tirednessLev(tirednessLevel::NONE), kb(nullptr) {};

void TirednessComponent::init() {
	kb = entity_->getComponent<KeyboardPlayerCtrl>();
	assert(kb != nullptr);
}

void TirednessComponent::sleep(int hours) {
	float tirednessRestored = ((hours * 100) / consts::MAX_SLEEP_HOURS) /100;
	tiredness += tirednessRestored;
	if (tiredness > 1.0f) tiredness = 1.0f;
	updateLevel();
}

void TirednessComponent::decreaseTiredness(float tiredness_) {
	tiredness -= tiredness_;
	if(tiredness < 0.0f) tiredness = 0.0f;
	updateLevel();
}

void TirednessComponent::calculatePlayerSpeed() const {
	float vel = consts::PLAYER_SPEED;

	if (tiredness >= consts::NONETIRED_LEVEL) vel *= 1.0f;
	else if (tiredness >= consts::TIRED_LEVEL) vel *= 0.8f;
	else vel = vel *= 0.66f;

	kb->setMaxSpeed(vel);
}

void TirednessComponent::calculateTravelSpeed() const{
	//Aumentar el tiempo de viaje en base al nivel de cansancio del jugador
}

void TirednessComponent::updateLevel() {
	if (tiredness >= consts::NONETIRED_LEVEL) tirednessLev = tirednessLevel::NONE;
	else if (tiredness >= consts::TIRED_LEVEL) tirednessLev = tirednessLevel::TIRED;
	else tirednessLev = tirednessLevel::EXHAUSTED;

	calculatePlayerSpeed();
}
