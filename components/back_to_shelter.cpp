#include "back_to_shelter.h"
#include "..//sdlutils/InputHandler.h"
#include "../classes/game_scene.h"
#include "../classes/shelter_scene.h"

BackToShelter::BackToShelter(GameScene* scene) : InteractableElement("Vuelta a refugio"), scene_(scene) {}

void BackToShelter::init() {
	InteractableElement::init();
	player_ = entity_->getMngr()->getHandler<Player_hdlr>();
}

void BackToShelter::Interact() {
	scene_->changeState(new ShelterScene(scene_->getGame()));
}

void BackToShelter::update() {
	if (ih().isKeyDown(SDLK_e) && CheckCollision(player_->getComponent<Transform>())) Interact();
}