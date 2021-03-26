#include "hunger_component.h"
#include "../sdlutils/InputHandler.h"

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
