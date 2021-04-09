#include "pain_component.h"
#include "../classes/physiognomy.h"
#include "concussion_component.h"
#include "intoxication_component.h"
#include "../ecs/Manager.h"
#include "../components/weapon.h"
#include "../classes/weapon_behaviour.h"

void PainComponent::init() {
	phys = static_cast<Player*>(entity_)->getPhysiognomy();
	time = sdlutils().currRealTime();
	weapon = static_cast<Player*>(entity_)->getCurrentWeapon()->getWeaponMovement();
	originalDmg = weapon->getDamage();
	reduceWeaponDamage();
}

PainComponent::~PainComponent() {
	weapon->setDamage(originalDmg);
}

void PainComponent::increaseTime() {
	for (int i = 0; i < phys->getNumStates(); i++) {
		auto component = phys->getHealthComponents()->operator[](i);
		if (dynamic_cast<ConcussionComponent*>(component) != nullptr) {
			static_cast<ConcussionComponent*>(component)->increaseTime(consts::CONTUSION_INCREASE_TIME);
		}
		else if (dynamic_cast<IntoxicationComponent*>(component) != nullptr) {
			static_cast<IntoxicationComponent*>(component)->increaseTime(consts::INTOXICATION_INCREASE_TIME);
		}
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
