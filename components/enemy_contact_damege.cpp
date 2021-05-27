#include "enemy_contact_damege.h"

#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../classes/physiognomy.h"
#include "../components/enemy_animation.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/SoundManager.h"

void EnemyContactDamage::init() {
	tr = entity_->getComponent<Transform>();
}

void EnemyContactDamage::update()
{
	if (!canCollide && sdlutils().currRealTime() - 2000 > cooldown) {
		canCollide = true;
		cooldown = sdlutils().currRealTime();
	}
}

void EnemyContactDamage::OnCollision(Entity* other)
{
	if (canCollide) {
		if (other->hasGroup<Enemy_grp>()) {
			//aplicar efecto x metiendo el componente necesario
			if (other->hasGroup<DefaultEnemy_grp>()) {
				physiognomy->addBleedState();
				other->getComponent<EnemyAnimation>()->setAttack(true);
				entity_->getComponent<PlayerAnimation>()->setDmg(true);
				soundManager().playSFX("hurt");
			}
			else if (other->hasGroup<FlyingEnemy_grp>()) {
				//aleatorio entre Pain y Intoxication
				int rand = sdlutils().rand().nextInt(0, 101);
				if(rand < 50) physiognomy->addPainState();
				else physiognomy->addIntoxicationState();
				other->getComponent<FlyingEnemyAnimation>()->setAttack(true);
				entity_->getComponent<PlayerAnimation>()->setDmg(true);
				soundManager().playSFX("hurt");
			}
			canCollide = false;
			cooldown = sdlutils().currRealTime();
		}

	}
}