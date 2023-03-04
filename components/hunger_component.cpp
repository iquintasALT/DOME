#include "hunger_component.h"
#include "../sdlutils/InputHandler.h"

HungerComponent::HungerComponent() : hunger(1.0f), hungerLev(hungerLevel::NONE) {}

void HungerComponent::eat(float hunger_) {
	hunger += hunger_;
	updateLevel();
}

void HungerComponent::updateLevel() {
	if (hunger >= consts::HUNGER_THRESHOLD) hungerLev = hungerLevel::NONE;
	else if (hunger >= consts::STARVATION_THRESHOLD) hungerLev = hungerLevel::HUNGRY;
	else hungerLev = hungerLevel::STARVING;
}
float HungerComponent::bleedoutSpeed() {
	// Returns between 1 (min hunger) and 2 (max hunger)
	if (hunger < consts::STARVATION_THRESHOLD)
		return 2.0;
	if (hunger < consts::HUNGER_THRESHOLD)
		return 1.5;
	return 1.0;
}
void HungerComponent::setHunger(float hunger_) {
	hunger = hunger_;
	updateLevel();
}
void HungerComponent::decreaseHunger(float hunger_) {
	hunger -= hunger_;
	if (hunger < 0.2) hunger = 0.2;
	updateLevel();
}
float HungerComponent::getHunger() {
	return hunger;
}
