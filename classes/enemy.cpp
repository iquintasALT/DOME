#include "enemy.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"
#include "../components/Transform.h"
#include "../components/player_animation.h"
#include "../components/GravityComponent.h"
#include "../components/Image.h"
#include "../components/KeyboardPlayerCtrl.h"

Entity* Enemy::newEnemy(Manager* mngr_, Point2D pos)
{
	Entity* enemy = mngr_->addEntity();
	enemy->addComponent<Transform>(pos, Vector2D(), 32, 64, 0);
	enemy->addComponent<GravityComponent>();
	enemy->addComponent<Image>(&sdlutils().images().at("player"), 2, 14, 0, 0);
	enemy->addComponent<player_animation>();
	enemy->addComponent<KeyboardPlayerCtrl>();
	return enemy;
}