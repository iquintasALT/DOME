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
	auto resumeButton = new PauseButton(Vector2D(consts::WINDOW_WIDTH/2-128, 370), Vector2D(256, 64) ,&sdlutils().images().at("resumeButton"), resume, g_, mngr_);
	mngr_->addEntity(resumeButton);

	auto settingsButton = new PauseButton(Vector2D(consts::WINDOW_WIDTH / 2 - 128, 450), Vector2D(256, 64), &sdlutils().images().at("settingsButton"), settings, g_, mngr_);
	mngr_->addEntity(settingsButton);

	auto menuButton = new PauseButton(Vector2D(consts::WINDOW_WIDTH / 2 - 128, 530), Vector2D(256, 64), &sdlutils().images().at("mainmenuButton"), menu, g_, mngr_);
	mngr_->addEntity(menuButton);
}
void PauseScene::resume(Manager* mng) {
	ih().clearState();
	mng->ChangeScene(nullptr, SceneManager::SceneMode::REMOVE);
	mng->getGame()->currentScene = SCENES::RAID;
}

void PauseScene::settings(Manager* mng) {
	ih().clearState();
	mng->ChangeScene(new SettingsScene(mng->getGame()), SceneManager::SceneMode::ADDITIVE);
	mng->getGame()->currentScene = SCENES::SETTINGS;
}

void PauseScene::menu(Manager* mng) {
	ih().clearState();
	mng->ChangeScene(new MenuScene(mng->getGame()), SceneManager::SceneMode::SINGLE);
	mng->getGame()->currentScene = SCENES::MAINMENU;
}

