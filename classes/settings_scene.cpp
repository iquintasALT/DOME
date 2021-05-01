#include "settings_scene.h"
#include "pause_button.h"
#include "../components/Image.h"
#include "../components/Transform.h"

void SettingsScene::init() {
	ih().clearState();
	auto backButton = new PauseButton(Vector2D(consts::WINDOW_WIDTH / 8 - 128, consts::WINDOW_HEIGHT-consts::WINDOW_HEIGHT/8), Vector2D(256, 64), &sdlutils().images().at("backButton"), back, g_, mngr_);
	mngr_->addEntity(backButton);

	createVolumeBar(Vector2D(400, 200), Vector2D(300, 40));
}

void SettingsScene::createVolumeBar(Vector2D pos, Vector2D size) {

	auto bar = mngr_->addEntity();
	auto barTr = bar->addComponent<Transform>(pos, size.getX(), size.getY());
	bar->addComponent<Image>(&sdlutils().images().at("volumeBar"), true);
	mngr_->addRenderLayer<Interface>(bar);

	Vector2D leftButtPos = Vector2D(barTr->getPos().getX() - (barTr->getW()/4), barTr->getPos().getY());
	auto leftButton = new PauseButton(leftButtPos, Vector2D(32, barTr->getH()), &sdlutils().images().at("decreaseVolume"), decreaseVolume, g_, mngr_);

	Vector2D rightButtPos = Vector2D(barTr->getPos().getX() + barTr->getW() + (barTr->getW() / 8), barTr->getPos().getY());
	auto rightButton = new PauseButton(rightButtPos, Vector2D(32, barTr->getH()), &sdlutils().images().at("raiseVolume"), raiseVolume, g_, mngr_);

	mngr_->addEntity(rightButton); mngr_->addEntity(leftButton);

	auto adjuster = mngr_->addEntity();
	adjuster->addComponent<Transform>(Vector2D(barTr->getPos().getX() + (barTr->getW() / 2)-16, barTr->getPos().getY()), 16,64);
	adjuster->addComponent<Image>(&sdlutils().images().at("volumeAdjuster"), true);
	mngr_->addRenderLayer<Interface>(adjuster);

}

void SettingsScene::back(Manager* mng) {
	mng->ChangeScene(nullptr, SceneManager::SceneMode::REMOVE);
}

void SettingsScene::raiseVolume(Manager* mng) {
	ih().clearState();
	auto actVolume = soundManager().getMusicVolume(); auto maxVolume = soundManager().getMaxVolume();

	auto volumeToRaise = maxVolume / 6;
	if (actVolume + volumeToRaise <= maxVolume) {
		soundManager().setMusicVolume( actVolume + volumeToRaise);
	}
}

void SettingsScene::decreaseVolume(Manager* mng) {
	ih().clearState();
	auto actVolume = soundManager().getMusicVolume(); auto maxVolume = soundManager().getMaxVolume();

	auto volumeToDecrease = maxVolume / 6;
	if (actVolume - volumeToDecrease >= 0) {
		soundManager().setMusicVolume(actVolume - volumeToDecrease); 
	}
}

