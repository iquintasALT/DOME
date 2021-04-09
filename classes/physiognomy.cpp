#include "physiognomy.h"
#include "../components/bleedout_component.h"
#include "../components/pain_component.h"
#include "../components/concussion_component.h"
#include "../components/player_health_component.h"
#include "../components/intoxication_component.h"

void Physiognomy::addBleedState() {
	if(numBleedStates == 0) player->addComponent<BleedoutComponent>();
	healthComponents[numStates] = player->getComponent<BleedoutComponent>();

	numBleedStates++;
	numStates++;
}

void Physiognomy::addPainState() {
	if (!painAdded) {
		auto c = player->addComponent<PainComponent>();
		healthComponents[numStates] = c;
		numStates++;
		painAdded = true;
	}
	else player->getComponent<PainComponent>()->newState();
}

void Physiognomy::addIntoxicationState() {
	if (!intoxicationAdded) {
		auto c = player->addComponent<IntoxicationComponent>();
		healthComponents[numStates] = c;
		numStates++;
		intoxicationAdded = true;
	}
	else player->getComponent<IntoxicationComponent>()->newState();
}

void Physiognomy::addConcussionState() {
	if (!concussionAdded) {
		auto c = player->addComponent<ConcussionComponent>();
		healthComponents[numStates] = c;
		numStates++;
		concussionAdded = true;
	}
	else player->getComponent<ConcussionComponent>()->newState();
}

void Physiognomy::moveElems(int i) {
	for (int c = i; c < numStates - 1; c++) {
		healthComponents[c] = healthComponents[c + 1];
	}
}

void Physiognomy::removeBleedState() {
	assert(numBleedStates > 0);

	for (int i = numStates-1; i >= 0; i--) {
		if (static_cast<BleedoutComponent*>(healthComponents[i]) != nullptr) {
			if (numBleedStates == 1) player->removeComponent<BleedoutComponent>();
			moveElems(i);
			numBleedStates--;
			numStates--;

			return;
		}
	}
}

void Physiognomy::removePainState() {
	for (int i = numStates - 1; i >= 0; i--) {
		if (static_cast<PainComponent*>(healthComponents[i]) != nullptr) {
			player->removeComponent<PainComponent>();
			moveElems(i);
			painAdded = false;
			numStates--;

			return;
		}
	}
}

void Physiognomy::removeIntoxicationState() {
	for (int i = numStates - 1; i >= 0; i--) {
		if (static_cast<IntoxicationComponent*>(healthComponents[i]) != nullptr) {
			player->removeComponent<IntoxicationComponent>();
			moveElems(i);
			intoxicationAdded = false;
			numStates--;

			return;
		}
	}
}

void Physiognomy::reemoveConcussionState() {
	for (int i = numStates - 1; i >= 0; i--) {
		if (static_cast<ConcussionComponent*>(healthComponents[i]) != nullptr) {
			player->removeComponent<ConcussionComponent>();
			moveElems(i);
			concussionAdded = false;
			numStates--;

			return;
		}
	}
}

