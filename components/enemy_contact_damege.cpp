#include "enemy_contact_damege.h"

#include "../ecs/Entity.h"
#include "../ecs/Manager.h"

void EnemyContactDamage::init() {
	manager = entity_->getMngr();
	tr = entity_->getComponent<Transform>();
}

void EnemyContactDamage::update() {
	if (!collision) {
		auto player_tr = entity_->getMngr()->getHandler<Player_hdlr>()->getComponent<Transform>();
		if (Collisions::collides(tr->getPos(), tr->getW(), tr->getH(),
			player_tr->getPos(),player_tr->getW(), player_tr->getH())) {
			//aplicar efecto x metiendo el componente necesario
			cout << "enemigo choca a jugador" << cooldown <<  endl;
			collision = true;
		}
	}
	else {
		cooldown += consts::DELTA_TIME;
		if (cooldown > 2) {
			collision = false;
			cooldown = 0;
		}
	}
}