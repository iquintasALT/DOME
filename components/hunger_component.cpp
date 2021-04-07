#include "hunger_component.h"
#include "../sdlutils/InputHandler.h"
#include "../components/bleedout_component.h"


HungerComponent::HungerComponent() : hunger(1.0f), hungerLevel(hungerLevel::NONE) {}

void HungerComponent::eat(float hunger_) {
	hunger += hunger_;
	updateLevel();
}

void HungerComponent::updateLevel() {
	if (hunger >= consts::NONEHUNGER_LEVEL) hungerLevel = hungerLevel::NONE;
	else if (hunger >= consts::HUNGER_LEVEL) hungerLevel = hungerLevel::HUNGRY;
	else hungerLevel = hungerLevel::STARVING;
}
int HungerComponent::calculateBleedingSpeed() {
	return (hunger * consts::MAX_NEWDAMAGE_TIME);
}
void HungerComponent::setHunger(float hunger_) {
	hunger = hunger_;
}
