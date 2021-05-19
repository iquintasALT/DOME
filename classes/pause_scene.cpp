#include "pause_scene.h"
#include "../classes/pause_button.h"
#include "../sdlutils/SDLUtils.h"
#include "../game/Game.h"
#include "../classes/locations_scene.h"
#include "../classes/menu_scene.h"
#include "../game/Game.h"
#include "../classes/settings_scene.h"
//#include "../ecs/Manager.h";

void PauseScene::init() {
	ih().clearState();

	auto pixel = mngr_->addEntity();
	pixel->addComponent<Transform>(Vector2D(0, 0), consts::WINDOW_WIDTH, consts::WINDOW_HEIGHT);
	pixel->addComponent<Image>(&sdlutils().images().at("bgImageDark"), true);
	mngr_->addRenderLayer<Interface>(pixel);

	auto resumeButton = new PauseButton(Vector2D(consts::WINDOW_WIDTH * 0.5f - (256/2), consts::WINDOW_HEIGHT * 0.5), Vector2D(256, 64) ,&sdlutils().images().at("resumeButton"), resume, g_, mngr_);
	mngr_->addEntity(resumeButton);

	auto settingsButton = new PauseButton(Vector2D(consts::WINDOW_WIDTH * 0.5f - (256 / 2), consts::WINDOW_HEIGHT * 0.6), Vector2D(256, 64), &sdlutils().images().at("settingsButton"), settings, g_, mngr_);
	mngr_->addEntity(settingsButton);

	auto menuButton = new PauseButton(Vector2D(consts::WINDOW_WIDTH * 0.5f - (256 / 2), consts::WINDOW_HEIGHT * 0.7), Vector2D(256, 64), &sdlutils().images().at("mainmenuButton"), menu, g_, mngr_);
	mngr_->addEntity(menuButton);

}
void PauseScene::update() {
	GameScene::update();
	if (ih().keyDownEvent() && ih().isKeyDown(SDL_SCANCODE_ESCAPE)) {
		mngr_->getGame()->setFPSActive(true);
		mngr_->ChangeScene(nullptr, SceneManager::SceneMode::REMOVE);
		mngr_->getGame()->currentScene = SCENES::RAID;
		ih().clearState();
	}
}

void PauseScene::resume(Manager* mng) {
	ih().clearState();
	mng->getGame()->setFPSActive(true);
	mng->ChangeScene(nullptr, SceneManager::SceneMode::REMOVE);
}

void PauseScene::settings(Manager* mng) {
	ih().clearState();
	mng->ChangeScene(new SettingsScene(mng->getGame()), SceneManager::SceneMode::ADDITIVE);
}

void PauseScene::menu(Manager* mng) {
	ih().clearState();
	mng->getGame()->playerCreated = false;
	mng->getGame()->numDays = 0;
	mng->ChangeScene(new MenuScene(mng->getGame(), false), SceneManager::SceneMode::SINGLE);
}

