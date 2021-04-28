#include "locations_scene.h"
#include "../game/Game.h"
#include "../classes/raid_scene.h"
#include "../sdlutils/Texture.h"
#include "../components/Image.h"
#include "../sdlutils/SDLUtils.h"

void LocationsScene::init()
{
	auto background = mngr_->addEntity();
	background->addComponent<Transform>(Vector2D(sdlutils().width() / 2 - sdlutils().height() / 2, 0),
		sdlutils().height(), sdlutils().height());
	background->addComponent<Image>(&sdlutils().images().at("location_image"), 1, 3, 0, 0);
	mngr_->addRenderLayer<Background>(background);

	// this here is so we are aware that this is not roght but I need to wait till we have all locations srry
	loadLocationButtons();
}

void LocationsScene::loadLocationButtons() {
	string path = "./resources/tilemap/location_placements.tmx";
	tmx::Map positions;
	positions.load(path);

	auto& map_layers = positions.getLayers();
	for (auto& layer : map_layers) {
		if (layer->getType() != tmx::Layer::Type::Object)
			continue;

		tmx::ObjectGroup* object_layer = dynamic_cast<tmx::ObjectGroup*>(layer.get());

		auto& objs = object_layer->getObjects();

		for (auto obj : objs) {
			auto aabb = obj.getAABB();
			auto col = obj.getProperties()[0].getIntValue();
			auto row = obj.getProperties()[1].getIntValue();

			auto button = mngr_->addEntity();
			button->addComponent<Transform>(Vector2D(aabb.left, aabb.top), 75, 75);
			button->addComponent<Image>(&sdlutils().images().at("location_icons"), 2, 3, row, col);
			mngr_->addRenderLayer<Background>(button);
			locations.push_back(button);
		}
	}
}

void LocationsScene::changeToRaid(Game* g, int index) {
	g->getStateMachine()->changeState(new ShelterScene(g));
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
					if (i == 0 || i == 1) changeToRaid(g_, i);
					else anActualGoodName(g_);
					mouseClick = true;
					return;
				}
			}
		}
		else if (mouseClick) mouseClick = false;
	}
}

