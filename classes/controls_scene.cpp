#include "controls_scene.h"
#include "pause_button.h"
#include "menu_button.h"
#include "../sdlutils/SDLUtils.h"
#include "../game/constant_variables.h"
#include "locations_scene.h"
#include "menu_scene.h"

void ControlsScene::init()
{
	float size = 1.2f;
	auto a = mngr_->addEntity();
	std::vector<Texture*> textures(5);
	for (int i = 2; i < 7; i++) {
		std::string str = "bgImage" + std::to_string(i);
		textures[i-2] = &sdlutils().images().at(str);
	}
	a->addComponent<ScrollingBackGround>(consts::WINDOW_WIDTH * size, consts::WINDOW_HEIGHT * size, textures, .2, true);
	mngr_->addRenderLayer<Interface>(a);

	auto playButton = new PauseButton(Vector2D(0, 0), Vector2D(consts::WINDOW_WIDTH, consts::WINDOW_HEIGHT), &sdlutils().images().at("black"), goGame, g_, mngr_, 0, " ");
	mngr_->addEntity(playButton);

	auto controls = mngr_->addEntity();
	controls->addComponent<Transform>(Vector2D(0.0, 0.0))->setSize(sdlutils().width(), sdlutils().height());
	controls->addComponent<Image>(&sdlutils().images().at("controls"), 1, 3, 0, 1);
	mngr_->addRenderLayer<ULTIMATE>(controls);
}	


void ControlsScene::goGame(Manager* mngr) {
	ih().clearState();
	mngr->ChangeScene(new LocationsScene(mngr->getGame()), SceneManager::SceneMode::ADDITIVE);
}

void ControlsScene::update() {
	GameScene::update();
	if (ih().keyDownEvent()) {
		ih().clearState();
		mngr_->ChangeScene(new LocationsScene(mngr_->getGame()), SceneManager::SceneMode::ADDITIVE);
	}
}