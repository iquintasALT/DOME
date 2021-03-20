#include "raid_scene.h"

#include "../components/interactableElement.h"
#include "../classes/particleSystem.h"
#include "../components/loot.h"

void RaidScene::init() {
	string path = "./resources/tilemap/template.tmx";
	Map::addMap(mngr_, path);

	Player* player = new Player(mngr_, Point2D(200, 50));

	Enemy* enemy = new Enemy(mngr_, Point2D(750, 50));

	RangedEnemy* rangedEnemy = new RangedEnemy(mngr_, Point2D(800, 50));

	Entity* interactableElement = mngr_->addEntity();
	interactableElement->addComponent<Transform>(Vector2D(0, 500), Vector2D(), 100, 100, 0);
	interactableElement->addComponent<Image>(&sdlutils().images().at("panel"), 1, 1, 0, 0);
	Inventory* i = interactableElement->addComponent<Inventory>(5, 5);
	interactableElement->addComponent<Loot>("Hola nena");

	i->adjustPanelSize();
	i->storeDefaultItems();
}