#include "raid_scene.h"
#include "../game/Game.h"
#include "../components/loot.h"
#include "../components/back_to_shelter.h"
#include "hud.h"
#include "../classes/pause_scene.h"
#include "../classes/camera.h"
#include "../sdlutils/InputHandler.h"
#include "../components/TextWithBackGround.h"

void RaidScene::init() {
	loadMap(path_);

	Player* player = static_cast<Player*>(mngr_->getHandler<Player_hdlr>());

	Enemy* enemy = new FlyingEnemy(mngr_, Point2D(750, 50));
	Enemy* enemy2 = new FlyingEnemy(mngr_, Point2D(700, 50));
	Enemy* enemy3 = new DefaultEnemy(mngr_, Point2D(300, 50));

	hud* h = new hud(mngr_, new Transform(Vector2D(100, 100), 64, 64, 0), player);
	//RangedEnemy* rangedEnemy = new RangedEnemy(mngr_, Point2D(800, 50));

	Entity* interactableElement = mngr_->addEntity();
	interactableElement->addComponent<Transform>(Vector2D(20, 575), 64, 64, 0);
	interactableElement->addComponent<Image>(&sdlutils().images().at("wardrobe"), 7, 2, 4, 0);
	mngr_->addRenderLayer<Loot>(interactableElement);
	interactableElement->addComponent<Loot>("Hola nena", 5, 5);

	Entity* returnToShelter = mngr_->addEntity(); 
	returnToShelter->addComponent<Transform>(Vector2D(900, 600), 64, 64, 0);
	returnToShelter->addComponent<BackToShelter>(g_);
	returnToShelter->addComponent<Image>(&sdlutils().images().at("items"), 4, 3, 0, 0);
	mngr_->addRenderLayer<Loot>(returnToShelter);
}

void RaidScene::update() {
	GameScene::update();
	
	if (ih().keyDownEvent() && ih().isKeyDown(SDL_SCANCODE_ESCAPE)) {
		g_->getStateMachine()->pushState(new PauseScene(g_));
		g_->getStateMachine()->currentState()->init();
	}
}