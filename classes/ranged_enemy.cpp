#include "ranged_enemy.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/GravityComponent.h"
#include "../components/Image.h"
#include "../components/enemy_behaviour_component.h"
#include "../components/enemy_detection_component.h"
#include "../components/player_animation.h"
#include "../components/Transform.h"

RangedEnemy::RangedEnemy(Manager* mngr_, Point2D pos) : GameCharacter(mngr_){
	mngr_->addEntity(this);
	addComponent<Transform>(pos, Vector2D(), 32, 64, 0);
	addComponent<GravityComponent>();
	addComponent<Image>(&sdlutils().images().at("player"), 3, 14, 0, 0);
	//addComponent<player_animation>();
	addComponent<DistanceDetection>(consts::ACTIVATE_ENEMY_DISTANCE);
	addComponent<KeepDistance>(consts::RANGED_ENEMY_SPEED, consts::RANGED_ENEMY_MARGINDISTANCE, consts::RANGED_ENEMY_SHOOTDISTANCE);
}