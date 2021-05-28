#include "settings_scene.h"
#include "../components/image.h"
#include "../components/transform.h"
#include "../game/Game.h"
#include "../classes/check_button.h"
#include "../sdlutils/SoundManager.h"
#include "../components/hold_to_skip.h"
#include "../components/image.h"
#include "../components/text_with_background.h"
#include "../game/constant_variables.h"
#include <vector>

void SettingsScene::init() {
	ih().clearState();

	buttonBackground = (&sdlutils().images().at("buttonBackground"));
	buttonBackground->setAlpha(50);

	//BACKGROUND
	auto pixel = mngr_->addEntity();
	pixel->addComponent<Transform>(Vector2D(0, 0), consts::WINDOW_WIDTH, consts::WINDOW_HEIGHT);
	pixel->addComponent<Image>(&sdlutils().images().at("bgImageDark"), true);
	mngr_->addRenderLayer<Interface>(pixel);

	auto domeLogo = mngr_->addEntity();
	domeLogo->addComponent<Transform>(Vector2D(consts::WINDOW_WIDTH * 0.5f - (750 / 2), consts::WINDOW_HEIGHT * 0.02), 750, 381);
	domeLogo->addComponent<Image>(&sdlutils().images().at("logo"), true);
	mngr_->addRenderLayer<Interface>(domeLogo);

	//BOTON DE VOLVER ATR�S
	auto backButton = new PauseButton(Vector2D(consts::WINDOW_WIDTH * 0.03f, consts::WINDOW_HEIGHT * 0.05f), Vector2D(192, 48), &sdlutils().images().at("backButton"), back, g_, mngr_);
	mngr_->addEntity(backButton);

	posBarVolume = Vector2D(consts::WINDOW_WIDTH * 0.55f, consts::WINDOW_HEIGHT * 0.62f);
	posBarSFX = Vector2D(consts::WINDOW_WIDTH * 0.55f, consts::WINDOW_HEIGHT * 0.75f);

	auto volumeBarsSize = Vector2D(consts::VOLUME_BARS_SIZE_X, consts::VOLUME_BARS_SIZE_Y);

	adjusterVolume = createVolumeBar(posBarVolume, volumeBarsSize, raiseVolume, decreaseVolume, &sdlutils().images().at("mainVolumeText"));
	adjusterSFXVolume = createVolumeBar(posBarSFX, volumeBarsSize, raiseEffectsVolume, decreaseEffectsVolume, &sdlutils().images().at("effectsVolume"));

	mainVolumeTex = new Texture(sdlutils().renderer(), "Main Volume", sdlutils().fonts().at("Orbitron32"), build_sdlcolor(0x000000));
	effectsVolumeTex = new Texture(sdlutils().renderer(), "Effects Volume", sdlutils().fonts().at("Orbitron32"), build_sdlcolor(0x000000));
	showFPSTex = new Texture(sdlutils().renderer(), "Show FPS", sdlutils().fonts().at("Orbitron32"), build_sdlcolor(0x000000));

	setAdjusterPosition();
	createShowFPSBar();
	//createFullscreenToggle();
}

void SettingsScene::render() {
	GameScene::render();

	float y = 0.605f;
	SDL_Rect dest = { 0, consts::WINDOW_HEIGHT * y, consts::WINDOW_WIDTH , consts::WINDOW_HEIGHT / 3 }; 
	buttonBackground->render(dest);

	mainVolumeTex->render({ (int)(consts::WINDOW_WIDTH * 0.1f), (int)(consts::WINDOW_HEIGHT * 0.59f), 450, 80 });
	effectsVolumeTex->render({ (int)(consts::WINDOW_WIDTH * 0.1f), (int)(consts::WINDOW_HEIGHT * 0.72f), 450, 80 });
	showFPSTex->render({ (int)(consts::WINDOW_WIDTH * 0.1f), (int)(consts::WINDOW_HEIGHT * 0.84f), 350, 70 });
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
	Vector2D adjusterPos = Vector2D(barTr->getPos().getX() + (barTr->getW() / 2) - consts::ADJUSTER_SIZE_X / 2, barTr->getPos().getY() - consts::ADJUSTER_SIZE_Y / 5);
	auto adjusterTr = adjuster->addComponent<Transform>(adjusterPos, consts::ADJUSTER_SIZE_X, consts::ADJUSTER_SIZE_Y);
	adjuster->addComponent<Image>(&sdlutils().images().at("volumeAdjuster"), build_sdlrect(0, 0, consts::ADJUSTER_SIZE_X, consts::ADJUSTER_SIZE_Y), true);
	mngr_->addRenderLayer<Interface>(adjuster);

	return adjusterTr;
}

void SettingsScene::createShowFPSBar() {
	//Boton
	Vector2D showFPSButtonPos = Vector2D(adjusterVolume->getPos().getX() - consts::VOLUME_BARS_SIZE_Y / 2 + adjusterVolume->getW() / 2, consts::WINDOW_HEIGHT * 0.86f);
	auto fpsButton = new CheckButton(showFPSButtonPos, Vector2D(consts::VOLUME_BARS_SIZE_Y, consts::VOLUME_BARS_SIZE_Y), &sdlutils().images().at("fpsButton"), showFPS, g_, mngr_, g_->getFPSActive());
	mngr_->addEntity(fpsButton);
}

void SettingsScene::createFullscreenToggle() {
	//Texto
	auto text = mngr_->addEntity();
	auto textBarPosition = Vector2D(consts::WINDOW_WIDTH * 0.15f, consts::WINDOW_HEIGHT * 0.485f);
	text->addComponent<Transform>(textBarPosition, consts::SHOW_FPS_BAR_SIZE_X, consts::SHOW_FPS_BAR_SIZE_Y);
	text->addComponent<Image>(&sdlutils().images().at("fullscreenText"), build_sdlrect(0, 0, 256, 32), true);
	mngr_->addRenderLayer<Interface>(text);

	//Boton
	Vector2D fullscreenPos = Vector2D(adjusterVolume->getPos().getX() - consts::VOLUME_BARS_SIZE_Y / 2 + adjusterVolume->getW() / 2, consts::WINDOW_HEIGHT * 0.485f);
	auto fullScreenButton = new CheckButton(fullscreenPos, Vector2D(consts::VOLUME_BARS_SIZE_Y, consts::VOLUME_BARS_SIZE_Y), &sdlutils().images().at("fpsButton"), fullScreen, g_, mngr_, g_->fullscreen);
	mngr_->addEntity(fullScreenButton);
}

void SettingsScene::setAdjusterPosition() {
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
		soundManager().setMusicVolume(actVolume + volumeToRaise);
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

void SettingsScene::showFPS(Manager* mng) {
	mng->getGame()->setFPSActive(!mng->getGame()->getFPSActive());
}

void SettingsScene::fullScreen(Manager* mng) {
	mng->getGame()->fullscreen = !mng->getGame()->fullscreen;

	// TODO change camera scale
	if (mng->getGame()->fullscreen) {
		sdlutils().changeWindowSize(1900, 1080);
		Camera::mainCamera->setScale(Camera::mainCamera->getScale() * (1900.0 / consts::WINDOW_WIDTH));
	}
	else {
		sdlutils().changeWindowSize(consts::WINDOW_WIDTH, consts::WINDOW_HEIGHT);
		Camera::mainCamera->setScale(Camera::mainCamera->getScale() / (1900.0 / consts::WINDOW_WIDTH));
	}

	sdlutils().toggleFullScreen();
}

CreditsScene::CreditsScene(Game* g) : GameScene(g, std::string("credits")) {
	exit = false;
	t = 0;
	width = 1;
	margin = 0;
	holdToSkip = nullptr;
}

void CreditsScene::update() {
	mngr_->update();

	Transform* tr = nullptr;
	for (auto e : mngr_->getEntities()) {
		if (e == holdToSkip)
			continue;
		if (e->hasComponent<Transform>()) {
			tr = e->getComponent<Transform>();
			auto& pos = tr->getPos();
			pos = pos - Vector2D(0, 50 * consts::DELTA_TIME);
		}
	}

	if (tr != nullptr && tr->getPos().getY() < -tr->getH()) {
		exit = true;
	}
	if (exit) {
		t += consts::DELTA_TIME;

		if (t > 2) {
			mngr_->ChangeScene(nullptr, SceneManager::SceneMode::REMOVE);
		}
	}
}

void CreditsScene::init() {
	width = 0.8f;
	margin = 10;
	int y = consts::WINDOW_HEIGHT * 0.8f;

	int size = 70;
	holdToSkip = mngr_->addEntity();
	holdToSkip->addComponent<Transform>(Vector2D(consts::WINDOW_WIDTH - size - 10, consts::WINDOW_HEIGHT - size - 10), size, size);
	holdToSkip->addComponent<Image>(&sdlutils().images().at("holdToSkip"), true);
	holdToSkip->addComponent<HoldToSkip>(1.5, [this]() { mngr_->ChangeScene(nullptr, SceneManager::SceneMode::REMOVE); });
	mngr_->addRenderLayer<Interface>(holdToSkip);

	soundManager().playMusic("credits_theme");

	std::vector<std::vector<std::string>> arr = {
		{"T", "CREDITS"},
		{"TEAM SUREFFECT"},
		{" "},
		{"CRISTIAN RENE CASTILLO LEON", "IVAN SANCHEZ MIGUEZ"},
		{"IAGO QUINTAS DIZ", "PABLO FERNANDEZ ALVAREZ"},
		{"YOJHAN STEVEN GARCIA PENA", "AARON NAUZET MORENO SOSA"},
		{"EMILE DE KADT", "PABLO GONZALEZ ALVAREZ"},
		{" "},
		{"MUSIC"},
		{"ROYALTY FREE MUSIC"},
		{"https://soundcloud.com/royaltyfreebackgroundmusic/sets/creative-commons-music-dark-12"},
		{"SERPENT STUDIOS"},
		{"https://www.serpentsoundstudios.com/royalty-free-music/ambient"},
		{"ART OF SILENCE - by Uniq"},
		{"under a Creative Commons license (Creative Commons - International Recognition 4.0 - CC BY 4.0)"},
		{" "},
		{"HONORABLE MENTIONS"},
		{"ABEL MORO PAJE"},
		{"PABLO ETAYO "},
		{" "},
		{"AND ONE LAST BIG THANK YOU"},
		{"TO YOU <3"},
	};

	for (auto txtArray : arr) {
		if (txtArray[0] == "T") {
			if (txtArray.size() == 2)
				addTitle(txtArray[1], y);
			else
				addParallelTitle(txtArray[1], txtArray[2], y);
			continue;
		}

		if (txtArray.size() == 2) {
			addParallel(txtArray[0], txtArray[1], y);
			continue;
		}

		addText(txtArray[0], y);
	}
}


void CreditsScene::addTitle(std::string txt, int& y) {
	auto text = mngr_->addEntity();
	auto tr = text->addComponent<Transform>(Vector2D(consts::WINDOW_WIDTH / 2, y), consts::WINDOW_WIDTH * width, 32);
	text->addComponent<TextWithBackground>(txt,
		sdlutils().fonts().at("OrbitronBold32"), build_sdlcolor(0xffffffff), nullptr, false, 0, true);
	mngr_->addRenderLayer<Interface>(text);

	y += tr->getH() + margin;
}

void CreditsScene::addText(std::string txt, int& y) {
	auto text = mngr_->addEntity();
	auto tr = text->addComponent<Transform>(Vector2D(consts::WINDOW_WIDTH / 2, y), consts::WINDOW_WIDTH * width, 32);
	text->addComponent<TextWithBackground>(txt,
		sdlutils().fonts().at("Orbitron24"), build_sdlcolor(0xffffffff), nullptr, false, 0, true);
	mngr_->addRenderLayer<Interface>(text);

	y += tr->getH() + margin;
}


void CreditsScene::addParallelTitle(std::string txt, std::string txt2, int& y) {
	auto text = mngr_->addEntity();

	auto tr = text->addComponent<Transform>(Vector2D(consts::WINDOW_WIDTH / 4, y), consts::WINDOW_WIDTH * width / 2, 32);
	text->addComponent<TextWithBackground>(txt,
		sdlutils().fonts().at("OrbitronBold"), build_sdlcolor(0xffffffff), nullptr, false, 0, true);
	mngr_->addRenderLayer<Interface>(text);

	text = mngr_->addEntity();
	tr = text->addComponent<Transform>(Vector2D(consts::WINDOW_WIDTH / 4 * 3, y), consts::WINDOW_WIDTH * width / 2, 32);
	text->addComponent<TextWithBackground>(txt2,
		sdlutils().fonts().at("OrbitronBold"), build_sdlcolor(0xffffffff), nullptr, false, 0, true);
	mngr_->addRenderLayer<Interface>(text);

	y += tr->getH() + margin;
}


void CreditsScene::addParallel(std::string txt, std::string txt2, int& y) {
	int x = consts::WINDOW_WIDTH * (1 - width) / 2;

	auto text = mngr_->addEntity();
	auto tr = text->addComponent<Transform>(Vector2D(x, y), consts::WINDOW_WIDTH * width / 2, 32);
	text->addComponent<TextWithBackground>(txt,
		sdlutils().fonts().at("Orbitron24"), build_sdlcolor(0xffffffff), nullptr, false, 0, false);
	mngr_->addRenderLayer<Interface>(text);

	text = mngr_->addEntity();
	tr = text->addComponent<Transform>(Vector2D(x + consts::WINDOW_WIDTH / 2, y), consts::WINDOW_WIDTH * width / 2, 32);
	text->addComponent<TextWithBackground>(txt2,
		sdlutils().fonts().at("Orbitron24"), build_sdlcolor(0xffffffff), nullptr, false, 0, false);
	mngr_->addRenderLayer<Interface>(text);

	y += tr->getH() + margin;
}

