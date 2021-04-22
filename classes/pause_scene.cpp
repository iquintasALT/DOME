#include "pause_scene.h"
#include "../classes/menu_button.h"
#include "../sdlutils/SDLUtils.h"
#include "../game/Game.h"
#include "../classes/locations_scene.h"

void PauseScene::init() {
	ih().clearState();
	auto resumeButton = new MenuButton(Vector2D(20, 300), Vector2D(400, 50) ,&sdlutils().images().at("resumeButton"), resume, g_, mngr_);
	mngr_->addEntity(resumeButton);

	auto menuButton = new MenuButton(Vector2D(20, 500), Vector2D(400, 50), &sdlutils().images().at("resumeButton"), menu, g_, mngr_);
	mngr_->addEntity(menuButton);

	auto settingsButton = new MenuButton(Vector2D(20, 700), Vector2D(400, 50), &sdlutils().images().at("resumeButton"), settings, g_, mngr_);
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

