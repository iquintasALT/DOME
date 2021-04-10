#include "raid_scene.h"

#include "../components/interactableElement.h"
#include "../components/loot.h"

void RaidScene::init() {
	string path = "./resources/tilemap/template.tmx";
	loadMap(path);

	Player* player = new Player(mngr_, Point2D(200, 50));

	Enemy* enemy = new DefaultEnemy(mngr_, Point2D(750, 50));

	//RangedEnemy* rangedEnemy = new RangedEnemy(mngr_, Point2D(800, 50));

	Entity* interactableElement = mngr_->addEntity();
	interactableElement->addComponent<Transform>(Vector2D(20, 600), 64, 64, 0);
	interactableElement->addComponent<Image>(&sdlutils().images().at("items"), 4, 3, 0, 0);
	interactableElement->addComponent<Loot>("Hola nena", 5, 5);
}