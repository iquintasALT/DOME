#include "hunger_component.h"
#include "../sdlutils/InputHandler.h"

HungerComponent::HungerComponent() : hunger(1.0f), hungerLev(hungerLevel::NONE) {}

void HungerComponent::eat(float hunger_) {
	hunger += hunger_;
	updateLevel();
}

void HungerComponent::updateLevel() {
	if (hunger >= consts::NONEHUNGER_LEVEL) hungerLev = hungerLevel::NONE;
	else if (hunger >= consts::HUNGER_LEVEL) hungerLev = hungerLevel::HUNGRY;
	else hungerLev = hungerLevel::STARVING;
}
int HungerComponent::calculateBleedingSpeed() {
	return (hunger * consts::MAX_NEWDAMAGE_TIME);
}
void HungerComponent::setHunger(float hunger_) {
	hunger = hunger_;
	updateLevel();
}
void HungerComponent::decreaseHunger(float hunger_) {
	hunger -= hunger_;
	if (hunger < 0) hunger = 0;
	updateLevel();
}
float HungerComponent::getHunger() {
	return hunger;
}
