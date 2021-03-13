#include "raid_scene.h"

void RaidScene::init() {
	Entity* player = mngr_->addEntity();
	player->addComponent<Transform>(Point2D(), Vector2D(), 32, 64, 0);
	player->addComponent<Image>(&sdlutils().images().at("player"), 2, 14, 0, 0);
	player->addComponent<player_animation>();
	player->addComponent<GravityComponent>();
	player->addComponent<KeyboardPlayerCtrl>();
	player->addComponent<InventoryController>();

	mngr_->setHandler<Player>(player);

	Transform* playerTr = player->getComponent<Transform>();
	Vector2D playerPos = playerTr->getPos();

	Entity* weapon = mngr_->addEntity();
	weapon->addComponent<Transform>(Vector2D(playerPos.getX() + playerTr->getW() / 2, playerPos.getY() + playerTr->getW() * 0.4), Vector2D(), 32, 32, 0);
	weapon->addComponent<Image>(&sdlutils().images().at("weapons"), 3, 3, 2, 2);
	weapon->addComponent<WeaponBehaviour>();

	Enemy::newEnemy(mngr_, Point2D(10, 50));
}