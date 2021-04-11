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


//WHEN COLLISIONS ARE FIXED TO NOT DEPEND ON GRAVITY, COLLISIONS WILL BE MOVED TO BASE CLASS
Enemy::Enemy(Manager* mngr_, Point2D pos) : GameCharacter(mngr_)
{
	mngr_->addEntity(this)->setGroup<Contact_Dmg_grp>(true);
	addComponent<Transform>(pos, 32, 64, 0);
	addComponent<RigidBody>();
	addComponent<EnemyContactDamage>();
}

DefaultEnemy::DefaultEnemy(Manager* mngr_, Point2D pos) : Enemy(mngr_, pos)
{
	addComponent<PlayerCollisions>();
	Component* img = addComponent<Image>(&sdlutils().images().at("enemy"), 2, 9, 0, 0);
	mngr_->addRenderLayer<Enemy>(img);
	addComponent<enemy_animation>();
	addComponent<DistanceDetection>(consts::ACTIVATE_ENEMY_DISTANCE);
	addComponent<ChasePlayer>(consts::MELEE_ENEMY_SPEED, consts::MELEE_ENEMY_STOPDISTANCE);
}

FlyingEnemy::FlyingEnemy(Manager* mngr_, Point2D pos) : Enemy(mngr_, pos)
{
	Component* img = addComponent<Image>(&sdlutils().images().at("player"), 3, 14, 0, 0);
	mngr_->addRenderLayer<Enemy>(img);
	//addComponent<player_animation>();
	addComponent<DistanceDetection>(consts::ACTIVATE_ENEMY_DISTANCE);
	addComponent<FlyingChasePlayer>(consts::MELEE_ENEMY_SPEED / 2, consts::MELEE_ENEMY_STOPDISTANCE, 50.0, 40.0);
}