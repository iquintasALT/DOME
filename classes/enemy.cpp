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


Enemy::Enemy(Manager* mngr_, Point2D pos, bool hasGravity = true) : GameCharacter(mngr_)
{
	mngr_->addEntity(this)->setGroup<Enemy_grp>(true);
	addComponent<Transform>(pos, 32, 64, 0);
	addComponent<RigidBody>();
	addComponent<EnemyContactDamage>();
}

DefaultEnemy::DefaultEnemy(Manager* mngr_, Point2D pos) : Enemy(mngr_, pos)
{
	mngr_->addRenderLayer<Enemy>(this);
	addComponent<PlayerCollisions>();
	addComponent<Image>(&sdlutils().images().at("enemy"), 2, 9, 0, 0);
	addComponent<enemy_animation>();
	addComponent<DistanceDetection>(consts::ACTIVATE_ENEMY_DISTANCE);
	addComponent2<EnemyAttackComponent, GroundedMeleeAttack>();
	addComponent<ChasePlayer>(consts::MELEE_ENEMY_SPEED, consts::MELEE_ENEMY_STOPDISTANCE);
}

FlyingEnemy::FlyingEnemy(Manager* mngr_, Point2D pos) : Enemy(mngr_, pos, false)
{
	mngr_->addRenderLayer<Enemy>(this);
	addComponent<Image>(&sdlutils().images().at("flying_enemy"), 1, 4, 0, 0);
	addComponent<RigidBody>(Vector2D(), false);
	addComponent<DistanceDetection>(consts::ACTIVATE_ENEMY_DISTANCE);
	addComponent2<EnemyAttackComponent, MeleeAttack>();
	addComponent<FlyingChasePlayer>(consts::MELEE_ENEMY_SPEED / 2, consts::MELEE_ENEMY_STOPDISTANCE, consts::FLYING_ENEMY_HOVERHEIGHT, consts::FLYING_ENEMY_APPROACHDISTANCE);
}