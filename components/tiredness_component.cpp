#include "tiredness_component.h"
#include "../sdlutils/InputHandler.h"

void TirednessComponent::init() {
	kb = entity_->getComponent<KeyboardPlayerCtrl>();
	assert(kb != nullptr);
}

void TirednessComponent::sleep(int hours) {
	if (sleepLog.size() >= 3) sleepLog.pop_back();
	sleepLog.push_front(hours);
}
void TirednessComponent::calculatePlayerSpeed() {
	float vel = kb->getSpeed();
	vel *= tiredness;

	kb->setSpeed(vel);
}

void TirednessComponent::calculateTiredness() {
	int amount = 0;
	for (int a : sleepLog) amount += a;

	tiredness = amount / (PREVIOUS_DAYS * MAX_SLEEP_HOURS);
}

void TirednessComponent::updateLevel() {
	if (tiredness >= NONETIRED_LEVEL) tirednessLevel = tirednessLevel::NONE;
	else if (tiredness >= TIRED_LEVEL) tirednessLevel = tirednessLevel::TIRED;
	else tirednessLevel = tirednessLevel::EXHAUSTED;
}
