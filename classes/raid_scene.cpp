#include "raid_scene.h"
#include "../game/Game.h"
#include "hud.h"
#include "../classes/pause_scene.h"
#include "../classes/camera.h"
#include "../sdlutils/InputHandler.h"
#include "../components/transitionComponent.h";
#include "../components/TextWithBackGround.h"
#include "../components/loot.h"
#include "../classes/physiognomy.h"
#include "../classes/countdown.h"
#include "../components/parallax_component.h"
#include "../components/InitialCameraZoom.h"
#include "../components/CameraMovement.h"
void RaidScene::init() {
	loadMap(path_);

	timer = new Countdown(420);

	player = static_cast<Player*>(mngr_->getHandler<Player_hdlr>());
	raidTimeEnded = false;

	auto weapon = player->getCurrentWeapon();

	if (!weapon->isActive())
		weapon->setActive(true);

	hud* h = new hud(mngr_, new Transform(Vector2D(100, 100), 64, 64, 0), player, timer);

	createParallaxBackground(5);

	auto cameraZoom = mngr_->addEntity();
	cameraZoom->addComponent<InitialCameraZoom>(1.2, 2, [this]() {
		mngr_->getHandler<Player_hdlr>()->getComponent<CameraMovement>()->enabled = true;
		});

	createTransition();
}

void RaidScene::update() {
	GameScene::update();


	if (!raidTimeEnded) {
		if (!timer->keepPlaying()) {
			player->getPhysiognomy()->addHypothermiaState();
			raidTimeEnded = true;
		}
	}
	
	if (ih().keyDownEvent() && ih().isKeyDown(SDL_SCANCODE_ESCAPE)) {
		mngr_->getGame()->setShouldRenderFPS(false);
		mngr_->ChangeScene(new PauseScene(mngr_->getGame()), SceneManager::SceneMode::ADDITIVE);
	}
}

void RaidScene::createParallaxBackground(int numOfRep) {
	createParallaxLayer(0, &sdlutils().images().at("sky"), numOfRep);
	createParallaxLayer(0.2, &sdlutils().images().at("houses4"), numOfRep);
	createParallaxLayer(0.3, &sdlutils().images().at("houses3"), numOfRep);
	createParallaxLayer(0.4, &sdlutils().images().at("houses2"), numOfRep);
	createParallaxLayer(0.5, &sdlutils().images().at("houses1"), numOfRep);
	createParallaxLayer(0.6, &sdlutils().images().at("wall"), numOfRep);
	createParallaxLayer(0.7, &sdlutils().images().at("road"), numOfRep);
}
