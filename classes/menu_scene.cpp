#include "menu_scene.h"
#include "shelter_scene.h"
#include "raid_scene.h"
#include "../sdlutils/SDLUtils.h"
#include "../game/Game.h"

MenuScene::MenuScene(Game* g) {
	buttons.push_back(new MenuButton(Vector2D(2 * sdlutils().width() / 5, 3 * sdlutils().height() / 5),
		&sdlutils().images().at("weapons"), playShelter, g, mngr_));
	buttons.push_back(new MenuButton(Vector2D(4 * sdlutils().width() / 5, 3 * sdlutils().height() / 5),
		&sdlutils().images().at("weapons"), playRaid, g, mngr_));
}

void MenuScene::init() {
}

void MenuScene::playShelter(Game* g) {
	g->getStateMachine()->pushState(new ShelterScene());
}

void MenuScene::playRaid(Game* g) {
	g->getStateMachine()->pushState(new RaidScene());
}