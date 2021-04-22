#include "pause_scene.h"
#include "../classes/menu_button.h"
#include "../sdlutils/SDLUtils.h"
#include "../game/Game.h"
#include "../classes/locations_scene.h"

void PauseScene::init() {
	ih().clearState();
	auto resumeButton = new MenuButton(Vector2D(100, 100), &sdlutils().images().at("resumeButton"), resume, g_, mngr_);
	mngr_->addEntity(resumeButton);

	auto menuButton = new MenuButton(Vector2D(100, 500), &sdlutils().images().at("player"), menu, g_, mngr_);
	mngr_->addEntity(menuButton);
}
void PauseScene::resume(Game* g) {
	g->getStateMachine()->popState();
}

void PauseScene::settings(Game* g) {

}

void PauseScene::menu(Game* g) {

}

