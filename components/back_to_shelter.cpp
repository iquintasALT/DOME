#include "back_to_shelter.h"
#include "..//sdlutils/InputHandler.h"
#include "../classes/game_scene.h"
#include "../classes/shelter_scene.h"
#include "../classes/player.h"
#include "../classes/physiognomy.h"

#include "../classes/raid_scene.h"
#include "../DomeEvents.h"
#include "GlassHouse.h"

BackToShelter::BackToShelter(GameScene* scene) : InteractableElement("Go back to SHELTER"), scene_(scene) {}

void BackToShelter::init() {
	InteractableElement::init();
	player_ = entity_->getMngr()->getHandler<Player_hdlr>();
}

void BackToShelter::Interact() {
	GlassHouse::enqueue(new ReturnHome(static_cast<RaidScene*>(scene_)->getTime(), static_cast<Player*>(player_)->getPhysiognomy()->getWounds()));

	entity_->getMngr()->getGame()->setShouldRenderFPS(true);
	static_cast<Player*>(player_)->getPhysiognomy()->removeAllStates();
	entity_->getMngr()->ChangeScene(new ShelterScene(scene_->getGame()), SceneManager::SceneMode::OVERRIDE);
}

void BackToShelter::update() {
	//if (ih().isKeyDown(SDLK_e) && CheckCollision(player_->getComponent<Transform>())) Interact();
}