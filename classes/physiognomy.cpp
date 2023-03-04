#include "physiognomy.h"
#include "../components/bleedout_component.h"
#include "../components/bloodloss_component.h"
#include "../components/pain_component.h"
#include "../components/concussion_component.h"
#include "../components/player_health_component.h"
#include "../components/intoxication_component.h"
#include "../components/hypothermia_component.h"
#include "../classes/lose_scene.h"
#include "../game/Game.h"
#include <iostream>

void Physiognomy::checkAlive(WAYSTODIE way) {
	//std::cout << "Checking death. Current wounds: " << getNumStates() << ".  Current bloodloss level: " << (bloodlossCount != nullptr ? *bloodlossCount : 0) << "\n";
	if (getNumStates() < consts::MAX_MULTIPLE_STATES) playerAlive = true;
	else die(way);
}

void Physiognomy::addBleedout() {
	checkAlive(WAYSTODIE::BLEED);
	if (!player->hasComponent<BleedoutComponent>()) 
	{
		player->addComponent<BleedoutComponent>();
		healthComponents.insert(player->getComponent<BleedoutComponent>());
	}
}

void Physiognomy::increaseBloodloss()
{
	checkAlive(WAYSTODIE::BLEED);
	if (!player->hasComponent<BloodlossComponent>())
		bloodlossCount = (player->addComponent<BloodlossComponent>())->getCount();
	else
		++(*bloodlossCount);

		// Regardless of whether a new component was created, a new pointer to it is added to the set
	healthComponents.insert(player->getComponent<BloodlossComponent>());
}

void Physiognomy::addPainState() {
	checkAlive(WAYSTODIE::PAIN);
	if (!painAdded) {
		auto c = player->addComponent<PainComponent>();
		healthComponents.insert(c);
		painAdded = true;
	}
	else player->getComponent<PainComponent>()->reduceWeaponDamage();
	player->getWeapon()->addDispersion(35);
}

void Physiognomy::addIntoxicationState() {
	checkAlive(WAYSTODIE::INTOXICATION);
	if (!intoxicationAdded) {
		auto c = player->addComponent<IntoxicationComponent>();
		healthComponents.insert(c);
		intoxicationAdded = true;
	}
	else player->getComponent<IntoxicationComponent>()->increaseTime();
}

void Physiognomy::addConcussionState() {
	checkAlive(WAYSTODIE::CONTUSION);
	if (!concussionAdded) {
		auto c = player->addComponent<ConcussionComponent>();
		healthComponents.insert(c);
		concussionAdded = true;
	}
	else player->getComponent<ConcussionComponent>()->increaseTime();
}

void Physiognomy::removeBleedout() {
	for (auto i = healthComponents.begin(); i != healthComponents.end(); ++i)
	{
		if (dynamic_cast<BleedoutComponent*>(*i))
		{
			healthComponents.erase(i);
			break;
		}
	}
	player->removeComponent<BleedoutComponent>();
}

void Physiognomy::removeBloodloss() {
	if (!player->hasComponent<BloodlossComponent>())
		return;
	--(*bloodlossCount);

	for (auto i = healthComponents.begin(); i != healthComponents.end(); ++i)
	{
		if (dynamic_cast<BloodlossComponent*>(*i))
		{
			healthComponents.erase(i);
			break;
		}
	}
	
	if (*bloodlossCount <= 0)
	{
		bloodlossCount = nullptr;

		player->removeComponent<BloodlossComponent>();
	}
}

void Physiognomy::removePainState() {
	if (player->hasComponent<PainComponent>())
	{
		//healthComponents.remove(player->getComponent<PainComponent>());
		for (auto i = healthComponents.begin(); i != healthComponents.end(); ++i)
		{
			if (dynamic_cast<PainComponent*>(*i))
			{
				healthComponents.erase(i);
				break;
			}
		}
		player->removeComponent<PainComponent>();
		painAdded = false;
		player->getWeapon()->addDispersion(-35);
	}
}

void Physiognomy::removeIntoxicationState() {
	if (player->hasComponent<IntoxicationComponent>())
	{
		//healthComponents.remove(player->getComponent<IntoxicationComponent>());
		for (auto i = healthComponents.begin(); i != healthComponents.end(); ++i)
		{
			if (dynamic_cast<IntoxicationComponent*>(*i))
			{
				healthComponents.erase(i);
				break;
			}
		}
		player->removeComponent<IntoxicationComponent>();
		intoxicationAdded = false;
	}
}

void Physiognomy::removeConcussionState() {
	if (player->hasComponent<ConcussionComponent>())
	{
		//healthComponents.remove(player->getComponent<ConcussionComponent>());
		for (auto i = healthComponents.begin(); i != healthComponents.end(); ++i)
		{
			if (dynamic_cast<ConcussionComponent*>(*i))
			{
				healthComponents.erase(i);
				break;
			}
		}
		player->removeComponent<ConcussionComponent>();
		concussionAdded = false;
	}
}

void Physiognomy::addHypothermiaState() {
	hypothermia = player->addComponent<HypothermiaComponent>();
}

void Physiognomy::removeHypothermiaState() {
	if (player->hasComponent<HypothermiaComponent>()) {
		//player->removeComponent<HypothermiaComponent>();
		for (auto i = healthComponents.begin(); i != healthComponents.end(); ++i)
		{
			if (dynamic_cast<HypothermiaComponent*>(*i))
			{
				healthComponents.erase(i);
				break;
			}
		}
		hypothermia = nullptr;
	}
}

void Physiognomy::removeAllStates() {
	removeBleedout();

	removeConcussionState();
	removeIntoxicationState();
	removePainState();
	removeHypothermiaState();
}

int Physiognomy::getNumStates()
{
	return healthComponents.size();
}

bool Physiognomy::isAlive() const {
	return playerAlive;
}

void Physiognomy::die(WAYSTODIE way) {
	playerAlive = false;
	removeAllStates();
	player->getMngr()->ChangeScene(new LoseScene(player->getMngr()->getGame(), way), SceneManager::SceneMode::ADDITIVE);
}
