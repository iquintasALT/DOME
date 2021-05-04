#include "menu_scene.h"
#include "shelter_scene.h"
#include "raid_scene.h"
#include "../sdlutils/SDLUtils.h"
#include "../game/Game.h"
#include "locations_scene.h"
#include "../ecs/Manager.h"
#include "../classes/settings_scene.h"

void MenuScene::init() {
	auto pixel = mngr_->addEntity();
	pixel->addComponent<Transform>(Vector2D(0, 0), consts::WINDOW_WIDTH, consts::WINDOW_HEIGHT);
	pixel->addComponent<Image>(&sdlutils().images().at("pixel"), true);
	mngr_->addRenderLayer<Interface>(pixel);

	auto playButton = new PauseButton(Vector2D(consts::WINDOW_WIDTH / 2 - 128, 370), Vector2D(256, 64), &sdlutils().images().at("playButton"), playGame, g_, mngr_);
	mngr_->addEntity(playButton);

	auto settingsButton = new PauseButton(Vector2D(consts::WINDOW_WIDTH / 2 - 128, 450), Vector2D(256, 64), &sdlutils().images().at("settingsButton"), settings, g_, mngr_);
	mngr_->addEntity(settingsButton);

	auto exitButton = new PauseButton(Vector2D(consts::WINDOW_WIDTH / 2 - 128, 530), Vector2D(256, 64), &sdlutils().images().at("exitButton"), exit, g_, mngr_);
	mngr_->addEntity(exitButton);
}

void MenuScene::playGame(Manager* mngr) {
	ih().clearState();
	mngr->ChangeScene(new LocationsScene(mngr->getGame()), SceneManager::SceneMode::ADDITIVE);
}

void MenuScene::settings(Manager* mngr) {
	ih().clearState();
	mngr->ChangeScene(new SettingsScene(mngr->getGame()), SceneManager::SceneMode::ADDITIVE);
	mngr->getGame()->currentScene = SCENES::SETTINGS;
}

void MenuScene::exit(Manager* mngr) {
	mngr->getGame()->quitGame();
}
