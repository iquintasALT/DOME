#include "raid_scene.h"

void RaidScene::init() {

	Player* player = new Player(mngr_, Point2D(10, 50));

	string path = "./resources/tilemap/template.tmx";
	Enemy::newEnemy(mngr_, Point2D(60, 50));
	Map::addMap(mngr_, path);
}