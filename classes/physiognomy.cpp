#include "physiognomy.h"
#include "../components/bleedout_component.h"
#include "../components/pain_component.h"
#include "../components/concussion_component.h"
#include "../components/player_health_component.h"
#include "../components/intoxication_component.h"

void Physiognomy::addBleedState() {
	assert(numStates < consts::MAX_MULTIPLE_STATES);
	if (numStates < consts::MAX_MULTIPLE_STATES) {
		if (numBleedStates == 0) player->addComponent<BleedoutComponent>();
		healthComponents[numStates] = player->getComponent<BleedoutComponent>();

		numBleedStates++;
		numStates++;
	}
}

void Physiognomy::addPainState() {
	assert(numStates < consts::MAX_MULTIPLE_STATES);
	if (!painAdded) {
		auto c = player->addComponent<PainComponent>();
		healthComponents[numStates] = c;
		numStates++;
		painAdded = true;
	}
	else player->getComponent<PainComponent>()->reduceWeaponDamage();
}

void Physiognomy::addIntoxicationState() {
	assert(numStates < consts::MAX_MULTIPLE_STATES);
	if (!intoxicationAdded) {
		auto c = player->addComponent<IntoxicationComponent>();
		healthComponents[numStates] = c;
		numStates++;
		intoxicationAdded = true;
	}
	else player->getComponent<IntoxicationComponent>()->increaseTime();
}

void Physiognomy::addConcussionState() {
	assert(numStates < consts::MAX_MULTIPLE_STATES);
	if (!concussionAdded) {
		auto c = player->addComponent<ConcussionComponent>();
		healthComponents[numStates] = c;
		numStates++;
		concussionAdded = true;
	}
	else player->getComponent<ConcussionComponent>()->increaseTime();
}

void Physiognomy::moveElems(int i) {
	for (int c = i; c < numStates - 1; c++) {
		healthComponents[c] = healthComponents[c + 1];
	}
}

void Physiognomy::removeBleedState() {
	assert(numStates > 0 && numBleedStates > 0);

	for (int i = numStates-1; i >= 0; i--) {
		if (dynamic_cast<BleedoutComponent*>(healthComponents[i]) != nullptr) {
			if (numBleedStates == 1) player->removeComponent<BleedoutComponent>();
			moveElems(i);
			numBleedStates--;
			numStates--;

			return;
		}
	}
}

void Physiognomy::removePainState() {
	assert(numStates > 0);
	for (int i = numStates - 1; i >= 0; i--) {
		if (dynamic_cast<PainComponent*>(healthComponents[i]) != nullptr) {
			player->removeComponent<PainComponent>();
			moveElems(i);
			painAdded = false;
			numStates--;

			return;
		}
	}
}

void Physiognomy::removeIntoxicationState() {
	assert(numStates > 0);
	for (int i = numStates - 1; i >= 0; i--) {
		if (dynamic_cast<IntoxicationComponent*>(healthComponents[i]) != nullptr) {
			player->removeComponent<IntoxicationComponent>();
			moveElems(i);
			intoxicationAdded = false;
			numStates--;

			return;
		}
	}
}

void Physiognomy::removeConcussionState() {
	assert(numStates > 0);
	for (int i = numStates - 1; i >= 0; i--) {
		if (dynamic_cast<ConcussionComponent*>(healthComponents[i]) != nullptr) {
			player->removeComponent<ConcussionComponent>();
			moveElems(i);
			concussionAdded = false;
			numStates--;

			return;
		}
	}
}

