#include "pause_scene.h"
#include "../classes/pause_button.h"
#include "../sdlutils/SDLUtils.h"
#include "../game/Game.h"
#include "../classes/locations_scene.h"
#include "../classes/menu_scene.h"

void PauseScene::init() {
	ih().clearState();
	auto resumeButton = new PauseButton(Vector2D(consts::WINDOW_WIDTH/2-128, 370), Vector2D(256, 64) ,&sdlutils().images().at("resumeButton"), resume, g_, mngr_);
	mngr_->addEntity(resumeButton);

	auto settingsButton = new PauseButton(Vector2D(consts::WINDOW_WIDTH / 2 - 128, 450), Vector2D(256, 64), &sdlutils().images().at("settingsButton"), settings, g_, mngr_);
	mngr_->addEntity(settingsButton);

	auto menuButton = new PauseButton(Vector2D(consts::WINDOW_WIDTH / 2 - 128, 530), Vector2D(256, 64), &sdlutils().images().at("mainmenuButton"), menu, g_, mngr_);
	mngr_->addEntity(menuButton);
}
void PauseScene::resume(Game* g) {
	ih().clearState();
	g->getStateMachine()->popState();
}

void PauseScene::settings(Game* g) {
	cout << "GO TO SETTINGS";
}

void PauseScene::menu(Game* g) {
	ih().clearState();
	g->getStateMachine()->~GameStateMachine();
	g->getStateMachine()->pushState(new MenuScene(g));
}

