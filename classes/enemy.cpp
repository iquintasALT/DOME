#include "enemy.h"

#include "../ecs/Manager.h"

#include "../sdlutils/SDLUtils.h"

#include "../components/transform.h"
#include "../components/enemy_animation.h"
#include "../components/image.h"
#include "../components/keyboard_player_ctrl.h"
#include "../components/enemy_behaviour_component.h"
#include "../components/enemy_detection_component.h"
#include "../components/enemy_attack_component.h"
#include "../components/box_collider.h"
#include "../components/particle_system.h"

Enemy::Enemy(Manager* mngr_, Point2D pos, bool hasGravity = true) : Entity(mngr_)
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
		createExplosion();
		setDead(true);
	}
}

void Enemy::createExplosion()
{
	auto tr = getComponent<Transform>();

	auto a = mngr_->addEntity();
	a->addComponent<Transform>(tr->getPos() + Vector2D(tr->getW(), tr->getH()) / 2.0);
	auto ap =a->addComponent<ParticleSystem>(&sdlutils().images().at("enemyDeath"), 1, 3, 0, 2);
	ap->particleScale = 1.5;
	ap->emitting = false;
	ap->burst = true;
	ap->burstCount = 10;
	ap->burstRepeat = 1;
	ap->destroyAfterBurst = true;
	ap->rateOverTime = 0;
	ap->lifeTime = 1;
	ap->burstDuration = 0.2f;
	ap->distanceToOrigin = tr->getW() / 2;
	ap->dir = Vector2D(0, 1);
	ap->angleDispersion = 150;
	ap->speed = 1.1;
	ap->gravityValue = 4;
	ap->offset = Vector2D(0, -10);
	ap->sizeCurve = ParticleSystem::Function(-1, 1);
	mngr_->addRenderLayer<Enemy>(a);

	a = mngr_->addEntity();
	a->addComponent<Transform>(tr->getPos() + Vector2D(tr->getW(), tr->getH()) / 2.0);
	ap = a->addComponent<ParticleSystem>(&sdlutils().images().at("enemyDeath"), 1, 3, 0, 0);
	ap->particleScale = 2;
	ap->emitting = false;
	ap->burst = true;
	ap->burstCount = 2;
	ap->burstRepeat = 1;
	ap->destroyAfterBurst = true;
	ap->rateOverTime = 0;
	ap->lifeTime =0.5;
	ap->burstDuration = 0.2f;
	ap->distanceToOrigin = tr->getW() / 4;
	ap->dir = Vector2D(0, 1);
	ap->angleDispersion = 90;
	ap->speed = 1.3;
	ap->gravityValue = 5;
	ap->offset = Vector2D(0, -10);
	ap->sizeCurve = ParticleSystem::Function(-1, 1);
	
	mngr_->addRenderLayer<Enemy>(a);
}

DefaultEnemy::DefaultEnemy(Manager* mngr_, Point2D pos) : Enemy(mngr_, pos)
{
	this->getComponent<Transform>()->setSize(38, 64);
	mngr_->addRenderLayer<Enemy>(this);
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