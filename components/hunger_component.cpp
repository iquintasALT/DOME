#include "hunger_component.h"
#include "../sdlutils/InputHandler.h"
#include "../components/bledout_component.h"

HungerComponent::HungerComponent() : hunger(1.0f), hungerLevel(hungerLevel::NONE) {}

void HungerComponent::eat(float hunger_) {
	hunger += hunger_;
	updateLevel();
}

void HungerComponent::updateLevel() {
	if (hunger >= NONEHUNGER_LEVEL) hungerLevel = hungerLevel::NONE;
	else if (hunger >= HUNGER_LEVEL) hungerLevel = hungerLevel::HUNGRY;
	else hungerLevel = hungerLevel::STARVING;
}
int HungerComponent::calculateBledingSpeed() {
	return (hunger * MAX_NEWDAMAGE_TIME) / 100;
}
