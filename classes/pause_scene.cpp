#include "pause_scene.h"
#include "../classes/menu_button.h"
#include "../sdlutils/SDLUtils.h"
#include "../game/Game.h"
#include "../classes/locations_scene.h"

void PauseScene::init() {
	ih().clearState();
	auto resumeButton = new MenuButton(Vector2D(consts::WINDOW_WIDTH/2-128, 370), Vector2D(265, 64) ,&sdlutils().images().at("resumeButton"), resume, g_, mngr_);
	mngr_->addEntity(resumeButton);

	auto menuButton = new MenuButton(Vector2D(consts::WINDOW_WIDTH / 2 - 128, 450), Vector2D(265, 64), &sdlutils().images().at("mainmenuButton"), menu, g_, mngr_);
	mngr_->addEntity(menuButton);

	auto settingsButton = new MenuButton(Vector2D(consts::WINDOW_WIDTH / 2 - 128, 530), Vector2D(265, 64), &sdlutils().images().at("settingsButton"), settings, g_, mngr_);
	mngr_->addEntity(settingsButton);
}
void PauseScene::resume(Game* g) {
	ih().clearState();
	g->getStateMachine()->popState();
}

void PauseScene::settings(Game* g) {

}

void PauseScene::menu(Game* g) {

}

