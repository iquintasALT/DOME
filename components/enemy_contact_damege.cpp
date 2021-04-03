#include "enemy_contact_damege.h"

#include "../ecs/Entity.h"
#include "../ecs/Manager.h"

void EnemyContactDamage::init() {
	manager = entity_->getMngr();
	tr = entity_->getComponent<Transform>();
}

void EnemyContactDamage::update() {
	//falta hacer
	//for (auto entity : entity_->getMngr()->getEnteties()) {
	//	if (entity->hasGroup<Contact_Dmg_grp>()) {
	//		auto e_tr = entity->getComponent<Transform>();
	//		if (Collisions::collides(tr->getPos(), tr->getW(), tr->getH(),
	//			e_tr->getPos(), e_tr->getW(), e_tr->getH())) {
	//			//aplicar efecto x metiendo el componente necesario
	//		}
	//	}
	//}
}