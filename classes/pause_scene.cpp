#include "pause_scene.h"
#include "../classes/pause_button.h"
#include "../sdlutils/SDLUtils.h"
#include "../game/Game.h"
#include "../classes/locations_scene.h"
#include "../classes/menu_scene.h"
#include "../game/Game.h"
#include "../classes/settings_scene.h"

#include "../DomeEvents/DomeEvents.h"
#include "GlassHouse.h"

void PauseScene::init() {
	ih().clearState();

	auto bg = mngr_->addEntity();
	bg->addComponent<Transform>(Vector2D(0, 0), consts::WINDOW_WIDTH, consts::WINDOW_HEIGHT);
	bg->addComponent<Image>(&sdlutils().images().at("bgImageDark"), true);
	mngr_->addRenderLayer<Interface>(bg);

	auto buttonImg = &sdlutils().images().at("yojhanButton");
	buttonImg->setAlpha(50);
	Uint8 alpha = 50;

	float buttonHeight = 64;
	float ypos = consts::WINDOW_HEIGHT - buttonHeight * 3 - 40;
	auto resumeButton = new MainMenuButton(Vector2D(0, ypos), Vector2D(consts::WINDOW_WIDTH, buttonHeight), buttonImg, resume, g_, mngr_, 0, "Resume", 50);
	mngr_->addEntity(resumeButton);
	ypos += buttonHeight;
	auto settingsButton = new MainMenuButton(Vector2D(0, ypos), Vector2D(consts::WINDOW_WIDTH, buttonHeight), buttonImg, settings, g_, mngr_, 0, "Settings", 50);
	mngr_->addEntity(settingsButton);
	ypos += buttonHeight;
	auto menuButton = new MainMenuButton(Vector2D(0, ypos), Vector2D(consts::WINDOW_WIDTH, buttonHeight), buttonImg, menu, g_, mngr_, 0, "Main Menu", 50);
	mngr_->addEntity(menuButton);

	auto domeLogo = mngr_->addEntity();
	domeLogo->addComponent<Transform>(Vector2D(consts::WINDOW_WIDTH * 0.5f - (750 / 2), consts::WINDOW_HEIGHT * 0.05), 750, 381);
	domeLogo->addComponent<Image>(&sdlutils().images().at("logo"), true);
	mngr_->addRenderLayer<Interface>(domeLogo);
}

void PauseScene::update() {
	GameScene::update();
	if (ih().keyDownEvent() && ih().isKeyDown(SDL_SCANCODE_ESCAPE)) {
		mngr_->getGame()->setShouldRenderFPS(true);
		mngr_->ChangeScene(nullptr, SceneManager::SceneMode::REMOVE);
		ih().clearState();
	}
}

void PauseScene::resume(Manager* mng) {
	ih().clearState();
	mng->getGame()->setShouldRenderFPS(true);
	mng->ChangeScene(nullptr, SceneManager::SceneMode::REMOVE);
}

void PauseScene::settings(Manager* mng) {
	ih().clearState();
	mng->ChangeScene(new SettingsScene(mng->getGame()), SceneManager::SceneMode::ADDITIVE);
}

void PauseScene::menu(Manager* mng) 
{
	GlassHouse::enqueue(new LevelEnd());
	GlassHouse::enqueue(new GameEnd());

	ih().clearState();
	mng->getGame()->numDays = 0;
	mng->ChangeScene(new MenuScene(mng->getGame(), false), SceneManager::SceneMode::SINGLE);
}

