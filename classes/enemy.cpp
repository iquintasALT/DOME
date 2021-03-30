#include "enemy.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"
#include "../components/Transform.h"
#include "../components/player_animation.h"
#include "../components/GravityComponent.h"
#include "../components/Image.h"
#include "../components/KeyboardPlayerCtrl.h"
#include "../components/enemy_behaviour_component.h"
#include "../components/enemy_detection_component.h"
#include "../components/player_collisions.h"


//WHEN COLLISIONS ARE FIXED TO NOT DEPEND ON GRAVITY, COLLISIONS WILL BE MOVED TO BASE CLASS
Enemy::Enemy(Manager* mngr_, Point2D pos) : GameCharacter(mngr_)
{
	mngr_->addEntity(this)->setGroup<Contact_Dmg_grp>(true);
	addComponent<Transform>(pos, Vector2D(), 32, 64, 0);
	addComponent<Image>(&sdlutils().images().at("player"), 3, 14, 0, 0);
	addComponent<GravityComponent>();
	addComponent<PlayerCollisions>();
}

DefaultEnemy::DefaultEnemy(Manager* mngr_, Point2D pos) : Enemy(mngr_, pos)
{
	addComponent<GravityComponent>();
	addComponent<PlayerCollisions>();//**********
	addComponent<Image>(&sdlutils().images().at("player"), 3, 14, 0, 0);
	//addComponent<player_animation>();
	addComponent<DistanceDetection>(consts::ACTIVATE_ENEMY_DISTANCE);
	addComponent<ChasePlayer>(consts::MELEE_ENEMY_SPEED, consts::MELEE_ENEMY_STOPDISTANCE);
}

FlyingEnemy::FlyingEnemy(Manager* mngr_, Point2D pos) : Enemy(mngr_, pos)
{
	addComponent<Image>(&sdlutils().images().at("player"), 3, 14, 0, 0);
	//addComponent<player_animation>();
	addComponent<DistanceDetection>(consts::ACTIVATE_ENEMY_DISTANCE);
	addComponent<FlyingChasePlayer>(consts::MELEE_ENEMY_SPEED / 2, consts::MELEE_ENEMY_STOPDISTANCE, 50.0, 40.0);
}