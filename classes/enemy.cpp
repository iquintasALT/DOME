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
#include "../components/box_collider.h"


Enemy::Enemy(Manager* mngr_, Point2D pos, bool hasGravity = true) : GameCharacter(mngr_)
{
	mngr_->addEntity(this)->setGroup<Enemy_grp>(true);
	addComponent<Transform>(pos);
	addComponent<RigidBody>();
	addComponent<BoxCollider>(false, 1);
}	

void Enemy::receiveDamage(int damage_)
{
	lives -= damage_;
	if (getComponent<EnemyAnimation>() != nullptr && !getComponent<EnemyAnimation>()->isDamaged()) {
		getComponent<EnemyAnimation>()->setDamaged(true);
	}
	else if (getComponent<FlyingEnemyAnimation>() != nullptr && !getComponent<FlyingEnemyAnimation>()->isDamaged()) {
		getComponent<FlyingEnemyAnimation>()->setDamaged(true);
	}

	//usar constantes! 5 siendo max vida

	if (lives <= 0) {
		setDead(true);
	}
}

DefaultEnemy::DefaultEnemy(Manager* mngr_, Point2D pos) : Enemy(mngr_, pos)
{
	this->getComponent<Transform>()->setSize(38, 64);
	mngr_->addRenderLayer<Enemy>(this);
	addComponent<PlayerCollisions>();
	addComponent<Image>(&sdlutils().images().at("enemy"), 4, 9, 0, 0);
	addComponent<EnemyAnimation>();
	addComponent<DistanceDetection>(consts::ACTIVATE_ENEMY_DISTANCE);
	addComponent2<EnemyAttackComponent, GroundedMeleeAttack>();
	addComponent<ChasePlayer>(consts::MELEE_ENEMY_SPEED, consts::MELEE_ENEMY_STOPDISTANCE);

	setGroup<DefaultEnemy_grp>(true);
}

FlyingEnemy::FlyingEnemy(Manager* mngr_, Point2D pos) : Enemy(mngr_, pos, false)
{
	this->getComponent<Transform>()->setSize(32, 32);
	mngr_->addRenderLayer<Enemy>(this);
	addComponent<Image>(&sdlutils().images().at("flying_enemy"), 3, 4, 0, 0);
	addComponent<RigidBody>(Vector2D(), false);
	addComponent<DistanceDetection>(consts::ACTIVATE_ENEMY_DISTANCE);
	addComponent2<EnemyAttackComponent, MeleeAttack>();
	addComponent<FlyingEnemyAnimation>();
	addComponent<FlyingChasePlayer>(consts::MELEE_ENEMY_SPEED / 2, consts::MELEE_ENEMY_STOPDISTANCE, consts::FLYING_ENEMY_HOVERHEIGHT, consts::FLYING_ENEMY_APPROACHDISTANCE);
	setGroup<FlyingEnemy_grp>(true);
}

RangedEnemy::RangedEnemy(Manager* mngr_, Point2D pos) : Enemy(mngr_, pos) {
	this->getComponent<Transform>()->setSize(32, 64);
	mngr_->addRenderLayer<Enemy>(this);
	addComponent<Image>(&sdlutils().images().at("player"), 3, 14, 0, 0);
	addComponent<DistanceDetection>(consts::ACTIVATE_ENEMY_DISTANCE);
	addComponent2<EnemyAttackComponent, RangedAttack>();
	addComponent<KeepDistance>(consts::RANGED_ENEMY_SPEED, consts::RANGED_ENEMY_MARGINDISTANCE, consts::RANGED_ENEMY_SHOOTDISTANCE);
	setGroup<RangedEnemy_grp>(true);
}