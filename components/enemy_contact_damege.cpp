#include "enemy_contact_damege.h"

#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../classes/physiognomy.h"

void EnemyContactDamage::init() {
	tr = entity_->getComponent<Transform>();
}

void EnemyContactDamage::update()
{
	if (!canCollide && sdlutils().currRealTime() - 2000 > cooldown) {
		cout << "enemigo choca a jugador" << cooldown << endl;
		canCollide = true;
		cooldown = sdlutils().currRealTime();
	}//sdlutils().currRealTime() > time + consts::TIME_PER_NEWSUMOFTIME
	else canCollide = false;
}

void EnemyContactDamage::OnCollision(Entity* other)
{
	if (canCollide) {
		if (other->hasGroup<Enemy_grp>()) {
			//aplicar efecto x metiendo el componente necesario
			//if (other->hasGroup<DefaultEnemy_grp>()) physiognomy->addBleedState();
			//else if (other->hasGroup<FlyingEnemy_grp>()) physiognomy->addPainState();
			//else if (other->hasGroup<RangedEnemy_grp>()) physiognomy->addIntoxicationState();
		}
	}
}