#include "back_to_shelter.h"
#include "..//sdlutils/InputHandler.h"
#include "..//game/Game.h"

BackToShelter::BackToShelter(Game* g) : InteractableElement("Vuelta a refugio") {
	states = g->getStateMachine();
}

void BackToShelter::init() {
	InteractableElement::init();
	player = entity_->getMngr()->getHandler<Player_hdlr>();
}

void BackToShelter::Interact() {
	states->popState();
}

void BackToShelter::update() {
	if (ih().isKeyDown(SDLK_e) && CheckCollision(player->getComponent<Transform>())) Interact();
}