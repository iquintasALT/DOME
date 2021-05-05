#include "settings_scene.h"
#include "../components/Image.h"
#include "../components/Transform.h"

void SettingsScene::init() {
	ih().clearState();

	//BACKGROUND
	auto pixel = mngr_->addEntity();
	pixel->addComponent<Transform>(Vector2D(0, 0), consts::WINDOW_WIDTH, consts::WINDOW_HEIGHT);
	pixel->addComponent<Image>(&sdlutils().images().at("bgImageDark"), true);
	mngr_->addRenderLayer<Interface>(pixel);

	//BOTON DE VOLVER ATRÁS
	auto backButton = new PauseButton(Vector2D(consts::BACK_BUTTON_POSITION_X, consts::BACK_BUTTON_POSITION_Y), Vector2D(256, 64), &sdlutils().images().at("backButton"), back, g_, mngr_);
	mngr_->addEntity(backButton);

	posBarVolume = Vector2D(consts::VOLUME_BAR_POSITION_X, consts::VOLUME_BAR_POSITION_Y); 
	posBarSFX = Vector2D(consts::SFX_VOLUME_BAR_POSITION_X, consts::SFX_VOLUME_BAR_POSITION_Y);

	auto volumeBarsSize = Vector2D(consts::VOLUME_BARS_SIZE_X, consts::VOLUME_BARS_SIZE_Y);

	adjusterVolume = createVolumeBar(posBarVolume, volumeBarsSize, raiseVolume, decreaseVolume, &sdlutils().images().at("mainVolumeText"));
	adjusterSFXVolume = createVolumeBar(posBarSFX, volumeBarsSize, raiseEffectsVolume, decreaseEffectsVolume, &sdlutils().images().at("effectsVolume"));

	setAdjusterPosition();
}

Transform* SettingsScene::createVolumeBar(Vector2D pos, Vector2D size, CallBackOnClick* raise, CallBackOnClick* decrease, Texture* t) {

	//Barra
	auto bar = mngr_->addEntity();
	auto barTr = bar->addComponent<Transform>(pos, size.getX(), size.getY());
	bar->addComponent<Image>(&sdlutils().images().at("volumeBar"), true);
	mngr_->addRenderLayer<Interface>(bar);

	//Botones
	Vector2D leftButtPos = Vector2D(barTr->getPos().getX() - consts::CHANGE_VOLUME_BUTTON_SIZE_X - 16, barTr->getPos().getY());
	auto leftButton = new PauseButton(leftButtPos, Vector2D(32, barTr->getH()), &sdlutils().images().at("decreaseVolume"), decrease, g_, mngr_, VOLUME);

	Vector2D rightButtPos = Vector2D(barTr->getPos().getX() + barTr->getW() + 16, barTr->getPos().getY());
	auto rightButton = new PauseButton(rightButtPos, Vector2D(consts::CHANGE_VOLUME_BUTTON_SIZE_X, barTr->getH()), &sdlutils().images().at("raiseVolume"), raise, g_, mngr_, VOLUME);

	mngr_->addEntity(rightButton); mngr_->addEntity(leftButton);

	//Adjuster
	auto adjuster = mngr_->addEntity();
	Vector2D adjusterPos = Vector2D(barTr->getPos().getX() + (barTr->getW() / 2) - consts::ADJUSTER_SIZE_X / 2, barTr->getPos().getY() - consts::ADJUSTER_SIZE_Y/5);
	auto adjusterTr = adjuster->addComponent<Transform>(adjusterPos, consts::ADJUSTER_SIZE_X, consts::ADJUSTER_SIZE_Y);
	adjuster->addComponent<Image>(&sdlutils().images().at("volumeAdjuster"), build_sdlrect(0,0, consts::ADJUSTER_SIZE_X, consts::ADJUSTER_SIZE_Y),  true);
	mngr_->addRenderLayer<Interface>(adjuster);

	//Texto
	auto text = mngr_->addEntity();
	auto textBarPosition = Vector2D(consts::BAR_TEXT_POSITION_X, barTr->getPos().getY() + barTr->getH() / 2 - consts::BAR_TEXT_SIZE_Y/2);
	text->addComponent<Transform>(textBarPosition, consts::BAR_TEXT_SIZE_X, consts::BAR_TEXT_SIZE_Y);
	text->addComponent<Image>(t, build_sdlrect(0, 0, 256, 32), true);
	mngr_->addRenderLayer<Interface>(text);

	return adjusterTr;
}
void SettingsScene::setAdjusterPosition()
{
	currentVolume = soundManager().getMusicVolume();
	currentSFXVolume = soundManager().getSFXVolume();

	auto percent = 100 * currentVolume / soundManager().getMaxVolume();    auto y = consts::VOLUME_LEVELS * percent / 100;
	adjusterVolume->setPos(Vector2D(posBarVolume.getX() + ((consts::VOLUME_BARS_SIZE_X / consts::VOLUME_LEVELS) * y) - 8, adjusterVolume->getPos().getY()));

	percent = 100 * currentSFXVolume / soundManager().getMaxSfxVolume();    y = consts::VOLUME_LEVELS * percent / 100;
	adjusterSFXVolume->setPos(Vector2D(posBarSFX.getX() + ((consts::VOLUME_BARS_SIZE_X / consts::VOLUME_LEVELS) * y) - 8, adjusterSFXVolume->getPos().getY()));
}


//CALLBACKS

void SettingsScene::back(Manager* mng) {
	mng->ChangeScene(nullptr, SceneManager::SceneMode::REMOVE);
}

void SettingsScene::raiseVolume(Manager* mng) {
	ih().clearState();
	auto actVolume = soundManager().getMusicVolume(); auto maxVolume = soundManager().getMaxVolume();

	auto volumeToRaise = maxVolume / consts::VOLUME_LEVELS;
	if (actVolume + volumeToRaise <= maxVolume) {
		soundManager().setMusicVolume( actVolume + volumeToRaise);
	}

}

void SettingsScene::decreaseVolume(Manager* mng) {
	ih().clearState();
	auto actVolume = soundManager().getMusicVolume(); auto maxVolume = soundManager().getMaxVolume();

	auto volumeToDecrease = maxVolume / consts::VOLUME_LEVELS;
	if (actVolume - volumeToDecrease >= 0) {
		soundManager().setMusicVolume(actVolume - volumeToDecrease); 
	}
}

void SettingsScene::raiseEffectsVolume(Manager* mng)
{
	ih().clearState();
	auto actVolume = soundManager().getSFXVolume(); auto maxVolume = soundManager().getMaxSfxVolume();

	auto volumeToRaise = maxVolume / consts::VOLUME_LEVELS;
	if (actVolume + volumeToRaise <= maxVolume) {
		soundManager().setSFXVolume(actVolume + volumeToRaise);
	}
}

void SettingsScene::decreaseEffectsVolume(Manager* mng)
{
	ih().clearState();
	auto actVolume = soundManager().getSFXVolume(); auto maxVolume = soundManager().getMaxSfxVolume();

	auto volumeToDecrease = maxVolume / consts::VOLUME_LEVELS;
	if (actVolume - volumeToDecrease >= 0) {
		soundManager().setSFXVolume(actVolume - volumeToDecrease);
	}
}

