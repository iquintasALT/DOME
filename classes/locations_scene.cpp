#include "locations_scene.h"
#include "../game/Game.h"
#include "../classes/raid_scene.h"
#include "../sdlutils/Texture.h"
#include "../components/Image.h"
#include "../sdlutils/SDLUtils.h"

LocationsScene::LocationsScene(Game* g) : GameScene(g) {

}


void LocationsScene::init()
{
	auto background = mngr_->addEntity();
	background->addComponent<Transform>(Vector2D(sdlutils().width() / 2 - sdlutils().height() / 2, 0),
		sdlutils().height(), sdlutils().height());
	background->addComponent<Image>(&sdlutils().images().at("location_image"), 1, 3, 0, 0);
	mngr_->addRenderLayer<Background>(background);

	// this here is so we are aware that this is not roght but I need to wait till we have all locations srry

	int numLoc = 2;
	locations.clear();
	locations.reserve(numLoc);
	for (int i = 0; i < numLoc; ++i) {
		auto button = mngr_->addEntity();
		button->addComponent<Transform>(Vector2D(250 + 300 * i, 300), 75, 75);
		button->addComponent<Image>(&sdlutils().images().at("location_icons"), 2, 3, 0 + 1 * i, 0);
		mngr_->addRenderLayer<Background>(button);
		locations.push_back(button);
	}

	std::cout << "El puto tamaño del array: " << locations.size() << std::endl << std::endl << std::endl;
}


void LocationsScene::changeToRaid(Game* g, int index) {
	g->getStateMachine()->changeState(new RaidScene(paths[index], g));
	g->getStateMachine()->currentState()->init();
}

void LocationsScene::anActualGoodName(Game* g) {
	g->getStateMachine()->pushState(new ShelterScene(g));
	g->getStateMachine()->currentState()->init();
}

void LocationsScene::update() {
	for (int i = 0;  i < locations.size(); i++) {
		Vector2D mousePos(ih().getMousePos().first, ih().getMousePos().second);
		auto buttonTr = locations[i]->getComponent<Transform>();

		if (ih().getMouseButtonState(InputHandler::LEFT)) {
			if (!mouseClick) {
				if (Collisions::collides(mousePos, 1, 1, buttonTr->getPos(), buttonTr->getW(), buttonTr->getH())) {
					// THIS IS SO BAD IT'S BURNING MY SOUL
					if (i == 0) changeToRaid(g_, i);
					else {
						anActualGoodName(g_);}
					mouseClick = true;
					return;
				}
			}
		}
		else if (mouseClick) {
			mouseClick = false;
		}
	}
}

