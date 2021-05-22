#include "controls_scene.h"
#include "pause_button.h"
#include "menu_button.h"
#include "../sdlutils/SDLUtils.h"
#include "../game/constant_variables.h"
#include "locations_scene.h"
#include "menu_scene.h"

void ControlsScene::init() {
	auto background = mngr_->addEntity();
	background->addComponent<Transform>(Vector2D(0.0, 0.0), consts::WINDOW_WIDTH, consts::WINDOW_HEIGHT);
	background->addComponent<Image>(&sdlutils().images().at(bgImage), true);
	mngr_->addRenderLayer<Background>(background);

	controls = mngr_->addEntity();
	controls->addComponent<Transform>(Vector2D(0.0, 0.0))->setSize(sdlutils().width(), sdlutils().height());
	controls->addComponent<Image>(&sdlutils().images().at(images[0]), 1, 1, 0, 0, true);
	mngr_->addRenderLayer<Interface>(controls);
}

void ControlsScene::update() {
	GameScene::update();

	if (ih().getMouseButtonState(InputHandler::LEFT) || ih().keyDownEvent()) {
		if (cont < 4) {
			controls->removeComponent<Image>();
			controls->addComponent<Image>(&sdlutils().images().at(images[cont]), 1, 1, 0, 0, true);
			ih().clearState();
			cont++;
		}
		else {
			ih().clearState();
			mngr_->ChangeScene(new LocationsScene(mngr_->getGame()), SceneManager::SceneMode::OVERRIDE);
		}
	}
}