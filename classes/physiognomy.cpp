#include "physiognomy.h"
#include "../components/bleedout_component.h"
#include "../components/pain_component.h"
#include "../components/concussion_component.h"
#include "../components/player_health_component.h"
#include "../components/intoxication_component.h"
#include "../components/hypothermia_component.h"
#include "../classes/lose_scene.h"

void Physiognomy::checkAlive() {
	if (healthComponents.size() < consts::MAX_MULTIPLE_STATES) playerAlive = true;
	else die();
}

void Physiognomy::addBleedState() {
	checkAlive();
	if (healthComponents.size() < consts::MAX_MULTIPLE_STATES) {
		if (numBleedStates == 0) player->addComponent<BleedoutComponent>();
		healthComponents.push_back(player->getComponent<BleedoutComponent>());

		numBleedStates++;
	}
}

void Physiognomy::addPainState() {
	checkAlive();
	if (!painAdded) {
		auto c = player->addComponent<PainComponent>();
		healthComponents.push_front(c);
		painAdded = true;
	}
	else player->getComponent<PainComponent>()->reduceWeaponDamage();
}

void Physiognomy::addIntoxicationState() {
	checkAlive();
	if (!intoxicationAdded) {
		auto c = player->addComponent<IntoxicationComponent>();
		healthComponents.push_front(c);
		intoxicationAdded = true;
	}
	else player->getComponent<IntoxicationComponent>()->increaseTime();
}

void Physiognomy::addConcussionState() {
	checkAlive();
	if (!concussionAdded) {
		auto c = player->addComponent<ConcussionComponent>();
		healthComponents.push_front(c);
		concussionAdded = true;
	}
	else player->getComponent<ConcussionComponent>()->increaseTime();
}

void Physiognomy::removeBleedState() {

	switch (numBleedStates)
	{
	case 1:
		player->removeComponent<BleedoutComponent>();
	default:
		healthComponents.pop_back();
		break;
	}
		
}

void Physiognomy::removePainState() {
	PainComponent* c = player->getComponent<PainComponent>();
	if (c != nullptr)
	{
		healthComponents.remove(c);
		player->removeComponent<PainComponent>();
		painAdded = false;
	}
}

void Physiognomy::removeIntoxicationState() {
	IntoxicationComponent* c = player->getComponent<IntoxicationComponent>();
	if (c != nullptr)
	{
		healthComponents.remove(c);
		player->removeComponent<IntoxicationComponent>();
		intoxicationAdded = false;
	}
}

void Physiognomy::removeConcussionState() {
	ConcussionComponent* c = player->getComponent<ConcussionComponent>();
	if (c != nullptr)
	{
		healthComponents.remove(c);
		player->removeComponent<ConcussionComponent>();
		concussionAdded = false;
	}
}

void Physiognomy::addHypothermiaState() {
	hypothermia = player->addComponent<HypothermiaComponent>();
}

void Physiognomy::removeHypothermiaState() {
	if (player->getComponent<HypothermiaComponent>() != nullptr) {
		player->removeComponent<HypothermiaComponent>();
		hypothermia = nullptr;
	}
}

void Physiognomy::removeAllStates() {
	for (int i = 0; i < numBleedStates; i++) removeBleedState();
	removeConcussionState();
	removeIntoxicationState();
	removePainState();
	removeHypothermiaState();
}

bool Physiognomy::alive() {
	return playerAlive;
}
void Physiognomy::die() {
	playerAlive = false;
	removeAllStates();

	player->getMngr()->ChangeScene(new LoseScene(player->getMngr()->getGame()), SceneManager::SceneMode::ADDITIVE);
}

