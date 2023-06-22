#include "physiognomy.h"
#include "GlassHouse.h"

#include "../components/bleedout_component.h"
#include "../components/bloodloss_component.h"
#include "../components/pain_component.h"
#include "../components/concussion_component.h"
#include "../components/player_health_component.h"
#include "../components/intoxication_component.h"
#include "../components/hypothermia_component.h"

#include "../classes/lose_scene.h"

#include "../DomeEvents/IncludeEvents.h"

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

		GlassHouse::enqueue(new WoundStart(BLEED));
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
	if (!painAdded) 
	{
		auto c = player->addComponent<PainComponent>();
		healthComponents.insert(c);
		painAdded = true;

		GlassHouse::enqueue(new WoundStart(PAIN));
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

		GlassHouse::enqueue(new WoundStart(INTOXICATION));
	}
	else player->getComponent<IntoxicationComponent>()->increaseTime();
}

void Physiognomy::addConcussionState() {
	checkAlive(WAYSTODIE::CONTUSION);
	if (!concussionAdded) 
	{
		auto c = player->addComponent<ConcussionComponent>();
		healthComponents.insert(c);
		concussionAdded = true;

		GlassHouse::enqueue(new WoundStart(CONCUSSION)); 
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

	if(player->hasComponent<BleedoutComponent>()) GlassHouse::enqueue(new WoundEnd(BLEED));
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

		GlassHouse::enqueue(new WoundEnd(PAIN));
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

		GlassHouse::enqueue(new WoundEnd(INTOXICATION));
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

		GlassHouse::enqueue(new WoundEnd(CONCUSSION));
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
	GlassHouse::enqueue(new GameEnd());

	playerAlive = false;
	removeAllStates();
	player->getMngr()->ChangeScene(new LoseScene(player->getMngr()->getGame(), way), SceneManager::SceneMode::ADDITIVE);
}

std::list<Wound>* Physiognomy::getWounds() {
	std::list<Wound>* wounds = new std::list<Wound>();
	if (player->hasComponent<BleedoutComponent>()) wounds->push_back(BLEED);
	if (player->hasComponent<PainComponent>()) wounds->push_back(PAIN);
	if (player->hasComponent<IntoxicationComponent>()) wounds->push_back(INTOXICATION);
	if (player->hasComponent<ConcussionComponent>()) wounds->push_back(CONCUSSION);

	return wounds;
}