#include "physiognomy.h"
#include "../components/bleedout_component.h"
#include "../components/pain_component.h"
#include "../components/concussion_component.h"
#include "../components/player_health_component.h"
#include "../components/intoxication_component.h"
#include "../components/hypothermia_component.h"
#include "../classes/lose_scene.h"
#include "../game/Game.h"

void Physiognomy::checkAlive(WAYSTODIE way) {
	if (healthComponents.size() < consts::MAX_MULTIPLE_STATES) playerAlive = true;
	else die(way);
}

void Physiognomy::addBleedState() {
	checkAlive(WAYSTODIE::BLEED);
	if (healthComponents.size() < consts::MAX_MULTIPLE_STATES) {
		if (numBleedStates == 0) player->addComponent<BleedoutComponent>();
		healthComponents.push_back(player->getComponent<BleedoutComponent>());

		numBleedStates++;
	}
}

void Physiognomy::addPainState() {
	checkAlive(WAYSTODIE::PAIN);
	if (!painAdded) {
		auto c = player->addComponent<PainComponent>();
		healthComponents.push_front(c);
		painAdded = true;
	}
	else player->getComponent<PainComponent>()->reduceWeaponDamage();
	player->getWeapon()->addDispersion(25);
}

void Physiognomy::addIntoxicationState() {
	checkAlive(WAYSTODIE::INTOXICATION);
	if (!intoxicationAdded) {
		auto c = player->addComponent<IntoxicationComponent>();
		healthComponents.push_front(c);
		intoxicationAdded = true;
	}
	else player->getComponent<IntoxicationComponent>()->increaseTime();
}

void Physiognomy::addConcussionState() {
	checkAlive(WAYSTODIE::CONTUSION);
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
	case 0:
		break;
	case 1:
		player->removeComponent<BleedoutComponent>();
		numBleedStates--;
		if (numBleedStates < 0) numBleedStates = 0;
	default:
		healthComponents.pop_back();
		numBleedStates--;
		if (numBleedStates < 0) numBleedStates = 0;
		break;
	}
}

void Physiognomy::removePainState() {
	if (player->hasComponent<PainComponent>())
	{
		healthComponents.remove(player->getComponent<PainComponent>());
		player->removeComponent<PainComponent>();
		painAdded = false;
		player->getWeapon()->addDispersion(-25);
	}
}

void Physiognomy::removeIntoxicationState() {
	if (player->hasComponent<IntoxicationComponent>())
	{
		healthComponents.remove(player->getComponent<IntoxicationComponent>());
		player->removeComponent<IntoxicationComponent>();
		intoxicationAdded = false;
	}
}

void Physiognomy::removeConcussionState() {
	if (player->hasComponent<ConcussionComponent>())
	{
		healthComponents.remove(player->getComponent<ConcussionComponent>());
		player->removeComponent<ConcussionComponent>();
		concussionAdded = false;
	}
}

void Physiognomy::addHypothermiaState() {
	hypothermia = player->addComponent<HypothermiaComponent>();
}

void Physiognomy::removeHypothermiaState() {
	if (player->hasComponent<HypothermiaComponent>()) {
		player->removeComponent<HypothermiaComponent>();
		hypothermia = nullptr;
	}
}

void Physiognomy::removeAllStates() {
	for (int i = 0; i < numBleedStates; i++)
		removeBleedState();
	removeConcussionState();
	removeIntoxicationState();
	removePainState();
	removeHypothermiaState();
}

bool Physiognomy::isAlive() const {
	return playerAlive;
}
void Physiognomy::die(WAYSTODIE way) {
	playerAlive = false;
	removeAllStates();
	player->getMngr()->ChangeScene(new LoseScene(player->getMngr()->getGame(), way), SceneManager::SceneMode::ADDITIVE);
}

