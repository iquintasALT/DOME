#include "tiredness_component.h"
#include "../sdlutils/InputHandler.h"

TirednessComponent::TirednessComponent() : tiredness(1.0f), tirednessLevel(tirednessLevel::NONE), kb(nullptr) {};

void TirednessComponent::init() {
	kb = entity_->getComponent<KeyboardPlayerCtrl>();
	assert(kb != nullptr);
}

void TirednessComponent::sleep(int hours) {
	float tirednessRestored = ((hours * 100) / MAX_SLEEP_HOURS) /100;
	tiredness += tirednessRestored;
	if (tiredness > 1.0f) tiredness = 1.0f;
	updateLevel();
}

void TirednessComponent::calculatePlayerSpeed() const {
	float vel = kb->getSpeed();
	vel *= tiredness;

	kb->setSpeed(vel);
}
void TirednessComponent::increaseTiredness(float tiredness_) {
	tiredness -= tiredness_;
	if(tiredness < 0.0f) tiredness = 0.0f;
	updateLevel();
}
void TirednessComponent::calculateTravelSpeed() const{
	//Aumentar el tiempo de viaje en base al nivel de cansancio del jugador
}

void TirednessComponent::updateLevel() {
	if (tiredness >= NONETIRED_LEVEL) tirednessLevel = tirednessLevel::NONE;
	else if (tiredness >= TIRED_LEVEL) tirednessLevel = tirednessLevel::TIRED;
	else tirednessLevel = tirednessLevel::EXHAUSTED;
}
