#include "hunger_component.h"
#include "../sdlutils/InputHandler.h"

HungerComponent::HungerComponent() : hunger(1.0f), hungerLevel(hungerLevel::NONE) {}

void HungerComponent::init() {

}

void HungerComponent::eat(float hunger_) {
	hunger += hunger_;
	updateLevel();
}

void HungerComponent::updateLevel() {
	if (hunger >= NONEHUNGER_LEVEL) hungerLevel = hungerLevel::NONE;
	else if (hunger >= HUNGER_LEVEL) hungerLevel = hungerLevel::HUNGRY;
	else hungerLevel = hungerLevel::STARVING;
}
