#include "menu_scene.h"
#include "shelter_scene.h"
#include "raid_scene.h"
#include "../sdlutils/SDLUtils.h"
#include "../game/Game.h"

MenuScene::MenuScene(Game* g) {
	mngr_->addEntity(new MenuButton(Vector2D(1 * sdlutils().width() / 5, 2 * sdlutils().height() / 5),
		&sdlutils().images().at("weapons"), playShelter, g, mngr_));
	mngr_->addEntity(new MenuButton(Vector2D(3 * sdlutils().width() / 5, 2 * sdlutils().height() / 5),
		&sdlutils().images().at("weapons"), playRaid, g, mngr_));
}

void MenuScene::init() {
}

void MenuScene::playShelter(Game* g) {
	g->getStateMachine()->pushState(new ShelterScene());
	g->getStateMachine()->currentState()->init();
}

void MenuScene::playRaid(Game* g) {
	g->getStateMachine()->pushState(new RaidScene());
	g->getStateMachine()->currentState()->init();
}