#include "enemy.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"
#include "../components/Transform.h"
#include "../components/enemy_animation.h"
#include "../components/Image.h"
#include "../components/KeyboardPlayerCtrl.h"
#include "../components/enemy_behaviour_component.h"
#include "../components/enemy_detection_component.h"
#include "../components/enemy_attack_component.h"
#include "../components/player_collisions.h"
#include "../components/enemy_contact_damege.h"
#include "../components/box_collider.h"


Enemy::Enemy(Manager* mngr_, Point2D pos, bool hasGravity = true) : GameCharacter(mngr_)
{
	mngr_->addEntity(this)->setGroup<Enemy_grp>(true);
	addComponent<Transform>(pos);
	addComponent<RigidBody>();
	addComponent<BoxCollider>(false, 1);
	addComponent<EnemyContactDamage>();
}

void Enemy::receiveDamage()
{
	lives--;
	if (lives <= 0) {
		setDead(true);
	}
}

DefaultEnemy::DefaultEnemy(Manager* mngr_, Point2D pos) : Enemy(mngr_, pos)
{
	this->getComponent<Transform>()->setSize(32, 64);
	mngr_->addRenderLayer<Enemy>(this);
	addComponent<PlayerCollisions>();
	addComponent<Image>(&sdlutils().images().at("enemy"), 2, 9, 0, 0);
	addComponent<DistanceDetection>(consts::ACTIVATE_ENEMY_DISTANCE);
	addComponent2<EnemyAttackComponent, GroundedMeleeAttack>();
	addComponent<ChasePlayer>(consts::MELEE_ENEMY_SPEED, consts::MELEE_ENEMY_STOPDISTANCE);
	addComponent<enemy_animation>();
}

FlyingEnemy::FlyingEnemy(Manager* mngr_, Point2D pos) : Enemy(mngr_, pos, false)
{
	this->getComponent<Transform>()->setSize(32, 32);
	mngr_->addRenderLayer<Enemy>(this);
	addComponent<Image>(&sdlutils().images().at("flying_enemy"), 1, 4, 0, 0);
	addComponent<RigidBody>(Vector2D(), false);
	addComponent<DistanceDetection>(consts::ACTIVATE_ENEMY_DISTANCE);
	addComponent2<EnemyAttackComponent, MeleeAttack>();
	addComponent<flying_enemy_animation>();
	addComponent<FlyingChasePlayer>(consts::MELEE_ENEMY_SPEED / 2, consts::MELEE_ENEMY_STOPDISTANCE, consts::FLYING_ENEMY_HOVERHEIGHT, consts::FLYING_ENEMY_APPROACHDISTANCE);
}

RangedEnemy::RangedEnemy(Manager* mngr_, Point2D pos) : Enemy(mngr_, pos) {
	this->getComponent<Transform>()->setSize(32, 64);
	mngr_->addRenderLayer<Enemy>(this);
	addComponent<Image>(&sdlutils().images().at("player"), 3, 14, 0, 0);
	addComponent<DistanceDetection>(consts::ACTIVATE_ENEMY_DISTANCE);
	addComponent2<EnemyAttackComponent, RangedAttack>();
	addComponent<KeepDistance>(consts::RANGED_ENEMY_SPEED, consts::RANGED_ENEMY_MARGINDISTANCE, consts::RANGED_ENEMY_SHOOTDISTANCE);
}