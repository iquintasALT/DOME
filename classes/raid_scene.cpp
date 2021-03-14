#include "raid_scene.h"

void RaidScene::init() {

	Player* player = new Player(mngr_, Point2D(10, 50));
	Transform* playerTr = player->getComponent<Transform>();
	Vector2D playerPos = playerTr->getPos();


	Entity* weapon = mngr_->addEntity();
	weapon->addComponent<Transform>(Vector2D(playerPos.getX() + playerTr->getW() / 2, playerPos.getY() + playerTr->getW() * 0.4), Vector2D(), 32, 32, 0);
	weapon->addComponent<Image>(&sdlutils().images().at("weapons"), 3, 3, 2, 2);
	weapon->addComponent<WeaponBehaviour>();

	Enemy::newEnemy(mngr_, Point2D(10, 50));
}