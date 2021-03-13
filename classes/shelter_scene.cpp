#include "../classes/shelter_scene.h"

void ShelterScene::init() {
	Entity* player = mngr_->addEntity();
	player->addComponent<Transform>(Vector2D(), Vector2D(), 32, 64, 0);
	player->addComponent<Image>(&sdlutils().images().at("player"), 2, 14, 0, 0);
	player->addComponent<player_animation>();
	player->addComponent<GravityComponent>();
	player->addComponent<KeyboardPlayerCtrl>();

	mngr_->setHandler<Player>(player);
}