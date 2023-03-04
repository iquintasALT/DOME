#include "pain_component.h"
#include "../classes/physiognomy.h"
#include "concussion_component.h"
#include "intoxication_component.h"
#include "../ecs/Manager.h"
#include "../components/weapon.h"
#include "../classes/weapon_behaviour.h"
#include <list>

void PainComponent::init() {
	phys = static_cast<Player*>(entity_)->getPhysiognomy();
	frameIndex = 2;
	time = sdlutils().currRealTime();
	weapon = static_cast<Player*>(entity_)->getWeapon()->getCurrentWeapon();
	originalDmg = weapon->getDamage();
	reduceWeaponDamage();
}

PainComponent::~PainComponent() {
	weapon->setDamage(originalDmg);
}

void PainComponent::increaseTime() {

	list<PlayerHealthComponent*>::iterator i = phys->getHealthComponents()->begin();
	while (i != phys->getHealthComponents()->end())
	{
		if (dynamic_cast<ConcussionComponent*>(*i) != nullptr) {
			static_cast<ConcussionComponent*>(*i)->increaseTime(consts::CONCUSSION_INCREASE_TIME);
		}
		else if (dynamic_cast<IntoxicationComponent*>(*i) != nullptr) {
			static_cast<IntoxicationComponent*>(*i)->increaseTime(consts::INTOXICATION_INCREASE_TIME);
		}
		i++;
	}
}
void PainComponent::update() {
	if (sdlutils().currRealTime() > time + consts::TIME_PER_NEWSUMOFTIME) {
		time = sdlutils().currRealTime();
		increaseTime();
	}
}
void PainComponent::reduceWeaponDamage() {
	weapon->setDamage(weapon->getDamage() - (originalDmg * consts::REDUCE_WEAPON_DAMAGE));
}
