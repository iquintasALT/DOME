#include "raid_scene.h"

#include "../components/loot.h"
#include "../components/back_to_shelter.h"
#include "hud.h"
#include "../classes/camera.h"

void RaidScene::init() {
	loadMap(path_);

	Player* player = new Player(mngr_, Point2D(200, 50));

	Enemy* enemy = new FlyingEnemy(mngr_, Point2D(750, 50));
	Enemy* enemy2 = new FlyingEnemy(mngr_, Point2D(700, 50));
	Enemy* enemy3 = new DefaultEnemy(mngr_, Point2D(300, 50));

	hud* h = new hud(mngr_, new Transform(Vector2D(100, 100), 64, 64, 0), player);
	//RangedEnemy* rangedEnemy = new RangedEnemy(mngr_, Point2D(800, 50));

	Entity* interactableElement = mngr_->addEntity();
	interactableElement->addComponent<Transform>(Vector2D(20, 600), 64, 64, 0);
	interactableElement->addComponent<Image>(&sdlutils().images().at("items"), 4, 3, 0, 0);
	mngr_->addRenderLayer<Loot>(interactableElement);
	interactableElement->addComponent<Loot>("Hola nena", 5, 5);

	Entity* returnToShelter = mngr_->addEntity(); 
	returnToShelter->addComponent<Transform>(Vector2D(900, 600), 64, 64, 0);
	returnToShelter->addComponent<BackToShelter>(g_);
	returnToShelter->addComponent<Image>(&sdlutils().images().at("items"), 4, 3, 0, 0);
	mngr_->addRenderLayer<Loot>(returnToShelter);
}