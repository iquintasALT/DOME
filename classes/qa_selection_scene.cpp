#include "qa_selection_scene.h"

#include "../game/Game.h"
#include "../classes/raid_scene.h"
#include "../sdlutils/Texture.h"
#include "../components/Image.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/SoundManager.h"
#include "../ecs/Component.h"

void qa_selection_scene::init() {
	locationButton = mngr_->addEntity();
	locationButtonTr = locationButton->addComponent<Transform>(Vector2D(consts::WINDOW_WIDTH / 2 - 300, consts::WINDOW_HEIGHT / 2 - 500), 200, 100);
	locationButton->addComponent<Image>(&sdlutils().images().at("raidButton"), 1, 1, 0, 0, true);

	shelterButton = mngr_->addEntity();
	shelterButtonTr = shelterButton->addComponent<Transform>(Vector2D(consts::WINDOW_WIDTH / 2 + 100, consts::WINDOW_HEIGHT / 2 - 50), 200, 100);
	shelterButton->addComponent<Image>(&sdlutils().images().at("shelterButton"), 1, 1, 0, 0, true);
}

void qa_selection_scene::update() {
	locationButton->render();
	shelterButton->render();
}