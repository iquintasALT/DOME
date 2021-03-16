#include "enemy.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"
#include "../components/Transform.h"
#include "../components/player_animation.h"
#include "../components/GravityComponent.h"
#include "../components/Image.h"
#include "../components/KeyboardPlayerCtrl.h"
#include "../components/enemy_behaviour_component.h"

Enemy::Enemy(Manager* mngr_, Point2D pos) :GameCharacter(mngr_)
{
	mngr_->addEntity(this);
	addComponent<Transform>(pos, Vector2D(), 32, 64, 0);
	addComponent<GravityComponent>();
	addComponent<Image>(&sdlutils().images().at("player"), 2, 14, 0, 0);
	addComponent<player_animation>();
	addComponent<ChasePlayer>(consts::MELEE_ENEMY_SPEED, consts::MELEE_ENEMY_STOPDISTANCE);
}