#include "../classes/shelter_scene.h"
#include "../components/hunger_component.h"
#include "../components/tiredness_component.h"

void ShelterScene::init() {
	Entity* player = mngr_->addEntity();
	auto tr = player->addComponent<Transform>(Vector2D(), Vector2D(), 32, 64, 0);
	player->addComponent<Image>(&sdlutils().images().at("player"), 3, 14, 0, 0);
	player->addComponent<ParticleSystem>(&sdlutils().images().at("dust"), 1, 1, 0, 0);
	player->addComponent<GravityComponent>(tr);
	player->addComponent<KeyboardPlayerCtrl>();
	player->addComponent<player_animation>();
	player->addComponent<HungerComponent>(Vector2D(10, 10));
	player->addComponent<TirednessComponent>(Vector2D(150, 10));

	mngr_->setHandler<Player_hdlr>(player);
}