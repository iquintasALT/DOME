#include "settings_scene.h"
#include "../components/Image.h"
#include "../components/Transform.h"

void SettingsScene::init() {
	ih().clearState();

	auto pixel = mngr_->addEntity();
	pixel->addComponent<Transform>(Vector2D(0, 0), consts::WINDOW_WIDTH, consts::WINDOW_HEIGHT);
	pixel->addComponent<Image>(&sdlutils().images().at("pixel"), true);
	mngr_->addRenderLayer<Interface>(pixel);

	auto backButton = new PauseButton(Vector2D(consts::WINDOW_WIDTH / 8 - 120, consts::WINDOW_HEIGHT - consts::WINDOW_HEIGHT / 8), Vector2D(256, 64), &sdlutils().images().at("backButton"), back, g_, mngr_);
	mngr_->addEntity(backButton);

	posBarVolume = Vector2D(600, 100); 
	posBarSFX = Vector2D(600, 200);
	adjusterVolume = createVolumeBar(posBarVolume, Vector2D(300, 40), raiseVolume, decreaseVolume, &sdlutils().images().at("mainVolumeText"));
	adjusterSFXVolume = createVolumeBar(posBarSFX, Vector2D(300, 40), raiseEffectsVolume, decreaseEffectsVolume, &sdlutils().images().at("effectsVolume"));

	currentVolume = soundManager().getMusicVolume();
	currentSFXVolume = soundManager().getSFXVolume();

	auto percent = 100 * currentVolume / soundManager().getMaxVolume();    auto y = VOLUME_LEVELS * percent / 100;
	adjusterVolume->setPos(Vector2D(posBarVolume.getX()+((300/ VOLUME_LEVELS)*y)-8, adjusterVolume->getPos().getY()));

	percent = 100 * currentSFXVolume / soundManager().getMaxSfxVolume();    y = VOLUME_LEVELS * percent / 100;
	adjusterSFXVolume->setPos(Vector2D(posBarSFX.getX() + ((300 / VOLUME_LEVELS) * y) - 8, adjusterSFXVolume->getPos().getY()));
}

void SettingsScene::moveAdjuster(Vector2D mousePos)
{
	if (mousePos.getY() < posBarVolume.getY() + 40 && mousePos.getY() > posBarVolume.getY() - 15) {
		if (currentVolume < soundManager().getMusicVolume()) {
			adjusterVolume->setPos(Vector2D(adjusterVolume->getPos().getX() + 300 / VOLUME_LEVELS, adjusterVolume->getPos().getY()));
		}
		else if(currentVolume > soundManager().getMusicVolume()) adjusterVolume->setPos(Vector2D(adjusterVolume->getPos().getX() - 300 / VOLUME_LEVELS, adjusterVolume->getPos().getY()));
		currentVolume = soundManager().getMusicVolume();
	}
	else {
		if (currentSFXVolume < soundManager().getSFXVolume()) {
			adjusterSFXVolume->setPos(Vector2D(adjusterSFXVolume->getPos().getX() + 300 / VOLUME_LEVELS, adjusterSFXVolume->getPos().getY()));
		}
		else if (currentSFXVolume > soundManager().getSFXVolume()) adjusterSFXVolume->setPos(Vector2D(adjusterSFXVolume->getPos().getX() - 300 / VOLUME_LEVELS, adjusterSFXVolume->getPos().getY()));
		currentSFXVolume = soundManager().getSFXVolume();
	}
}

Transform* SettingsScene::createVolumeBar(Vector2D pos, Vector2D size, CallBackOnClick* raise, CallBackOnClick* decrease, Texture* t) {

	//Barra
	auto bar = mngr_->addEntity();
	auto barTr = bar->addComponent<Transform>(pos, size.getX(), size.getY());
	bar->addComponent<Image>(&sdlutils().images().at("volumeBar"), true);
	mngr_->addRenderLayer<Interface>(bar);

	//Botones
	Vector2D leftButtPos = Vector2D(barTr->getPos().getX() - 40, barTr->getPos().getY());
	auto leftButton = new PauseButton(leftButtPos, Vector2D(32, barTr->getH()), &sdlutils().images().at("decreaseVolume"), decrease, g_, mngr_, VOLUME);

	Vector2D rightButtPos = Vector2D(barTr->getPos().getX() + barTr->getW() + 7, barTr->getPos().getY());
	auto rightButton = new PauseButton(rightButtPos, Vector2D(32, barTr->getH()), &sdlutils().images().at("raiseVolume"), raise, g_, mngr_, VOLUME);

	mngr_->addEntity(rightButton); mngr_->addEntity(leftButton);

	//Adjuster
	auto adjuster = mngr_->addEntity();
	Vector2D adjusterPos = Vector2D(barTr->getPos().getX() + (barTr->getW() / 2) - 8, barTr->getPos().getY() - 12);
	auto adjusterTr = adjuster->addComponent<Transform>(adjusterPos, 16, 64);
	adjuster->addComponent<Image>(&sdlutils().images().at("volumeAdjuster"), build_sdlrect(0,0, 16, 64),  true);
	mngr_->addRenderLayer<Interface>(adjuster);

	//Texto
	auto text = mngr_->addEntity();
	text->addComponent<Transform>(Vector2D(barTr->getPos().getX() - 500, barTr->getPos().getY()+barTr->getH()/2-20), 320, 40);
	text->addComponent<Image>(t, build_sdlrect(0, 0, 256, 32), true);
	mngr_->addRenderLayer<Interface>(text);

	return adjusterTr;
}

void SettingsScene::back(Manager* mng) {
	mng->ChangeScene(nullptr, SceneManager::SceneMode::REMOVE);
}

void SettingsScene::raiseVolume(Manager* mng) {
	ih().clearState();
	auto actVolume = soundManager().getMusicVolume(); auto maxVolume = soundManager().getMaxVolume();

	auto volumeToRaise = maxVolume / VOLUME_LEVELS;
	if (actVolume + volumeToRaise <= maxVolume) {
		soundManager().setMusicVolume( actVolume + volumeToRaise);
	}

}

void SettingsScene::decreaseVolume(Manager* mng) {
	ih().clearState();
	auto actVolume = soundManager().getMusicVolume(); auto maxVolume = soundManager().getMaxVolume();

	auto volumeToDecrease = maxVolume / VOLUME_LEVELS;
	if (actVolume - volumeToDecrease >= 0) {
		soundManager().setMusicVolume(actVolume - volumeToDecrease); 
	}
}

void SettingsScene::raiseEffectsVolume(Manager* mng)
{
	ih().clearState();
	auto actVolume = soundManager().getSFXVolume(); auto maxVolume = soundManager().getMaxSfxVolume();

	auto volumeToRaise = maxVolume / VOLUME_LEVELS;
	if (actVolume + volumeToRaise <= maxVolume) {
		soundManager().setSFXVolume(actVolume + volumeToRaise);
	}
}

void SettingsScene::decreaseEffectsVolume(Manager* mng)
{
	ih().clearState();
	auto actVolume = soundManager().getSFXVolume(); auto maxVolume = soundManager().getMaxSfxVolume();

	auto volumeToDecrease = maxVolume / VOLUME_LEVELS;
	if (actVolume - volumeToDecrease >= 0) {
		soundManager().setSFXVolume(actVolume - volumeToDecrease);
	}
}

