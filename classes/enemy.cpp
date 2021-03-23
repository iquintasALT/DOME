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

Enemy::Enemy(Manager* mngr_, Point2D pos) : GameCharacter(mngr_)
{
	mngr_->addEntity(this)->setGroup<Contact_Dmg_grp>(true);
	addComponent<Transform>(pos, Vector2D(), 32, 64, 0);
	auto* gr = addComponent<GravityComponent>();
	addComponent<PlayerCollisions>(mngr_, gr);
	addComponent<Image>(&sdlutils().images().at("player"), 3, 14, 0, 0);
	//addComponent<player_animation>();
	addComponent<DistanceDetection>(consts::ACTIVATE_ENEMY_DISTANCE);
	addComponent<ChasePlayer>(consts::MELEE_ENEMY_SPEED, consts::MELEE_ENEMY_STOPDISTANCE);
}