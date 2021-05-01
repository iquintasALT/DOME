#include "settings_scene.h"
#include "pause_button.h"

void SettingsScene::init() {
	ih().clearState();
	auto backButton = new PauseButton(Vector2D(consts::WINDOW_WIDTH / 8 - 128, consts::WINDOW_HEIGHT-consts::WINDOW_HEIGHT/8), Vector2D(256, 64), &sdlutils().images().at("backButton"), back, g_, mngr_);
	mngr_->addEntity(backButton);
}

void SettingsScene::back(Manager* mng) {
	mng->ChangeScene(nullptr, SceneManager::SceneMode::REMOVE);
}

