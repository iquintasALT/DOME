#include "raid_scene.h"
#include "../game/Game.h"
#include "hud.h"
#include "../classes/pause_scene.h"
#include "../classes/camera.h"
#include "../sdlutils/InputHandler.h"
#include "../components/transitionComponent.h";
#include "../components/TextWithBackGround.h"
#include "../components/loot.h"

void RaidScene::init() {
	loadMap(path_);

	Player* player = static_cast<Player*>(mngr_->getHandler<Player_hdlr>());

	auto weapon = player->getCurrentWeapon();

	if (!weapon->isActive())
		weapon->setActive(true);

	hud* h = new hud(mngr_, new Transform(Vector2D(100, 100), 64, 64, 0), player);

	Entity* l = mngr_->addEntity();
	l->addComponent<Transform>(Vector2D(150, 556), 100, 100);
	l->addComponent<Image>(&sdlutils().images().at("dust"));
	l->addComponent<Loot>("Press E to open the loot", 5, 5);
	mngr_->addRenderLayer<Player>(l);

	createTransition();
}

void RaidScene::update() {
	GameScene::update();
	
	if (ih().keyDownEvent() && ih().isKeyDown(SDL_SCANCODE_ESCAPE)) {
		mngr_->ChangeScene(new PauseScene(mngr_->getGame()), SceneManager::SceneMode::ADDITIVE);
	}
}