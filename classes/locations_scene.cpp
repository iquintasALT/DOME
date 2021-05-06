#include "locations_scene.h"
#include "../game/Game.h"
#include "../classes/raid_scene.h"
#include "../sdlutils/Texture.h"
#include "../components/Image.h"
#include "../sdlutils/SDLUtils.h"

void LocationsScene::init()
{
	auto background = mngr_->addEntity();
	background->addComponent<Transform>(Vector2D(sdlutils().width() * 0.33 , 0),
		sdlutils().height(), sdlutils().height());
	background->addComponent<Image>(&sdlutils().images().at("location_image"), 1, 3, 0, 0, true);
	mngr_->addRenderLayer<Background>(background);

	auto info1 = mngr_->addEntity();
	info1->addComponent<Transform>(Vector2D(50, 0), 280, 630);
	info1->addComponent<Image>(&sdlutils().images().at("info_hospital"), 1, 1, 0, 0, true);
	info1->setActive(false);
	mngr_->addRenderLayer<Item>(info1);
	infos.push_back(info1);

	auto info2 = mngr_->addEntity();
	info2->addComponent<Transform>(Vector2D(50, 0), 280, 630);
	info2->addComponent<Image>(&sdlutils().images().at("info_comunicaciones"), 1, 1, 0, 0, true); //CAMBIAR ESTA IMAGEN AL TEXTO BIEN
	info2->setActive(false);
	mngr_->addRenderLayer<Item>(info2);
	infos.push_back(info2);

	auto info3 = mngr_->addEntity();
	info3->addComponent<Transform>(Vector2D(50, 0), 280, 630);
	info3->addComponent<Image>(&sdlutils().images().at("info_supermercado"), 1, 1, 0, 0, true);
	info3->setActive(false);
	mngr_->addRenderLayer<Item>(info3);
	infos.push_back(info3);

	auto info4 = mngr_->addEntity();
	info4->addComponent<Transform>(Vector2D(50, 0), 280, 630);
	info4->addComponent<Image>(&sdlutils().images().at("info_hospital"), 1, 1, 0, 0, true);
	info4->setActive(false);
	mngr_->addRenderLayer<Item>(info4);
	infos.push_back(info4);

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
			button->addComponent<Image>(&sdlutils().images().at("location_icons"), 2, 3, row, col, true);
			mngr_->addRenderLayer<Background>(button);
			locations.push_back(button);
		}
	}
}

void LocationsScene::changeToRaid(Game* g, int index) {
	g->currentScene = SCENES::RAID;
	mngr_->ChangeScene(new RaidScene(paths[index], names[index], g), SceneManager::SceneMode::OVERRIDE);
}

void LocationsScene::anActualGoodName(Game* g) {
	mngr_->ChangeScene(new ShelterScene(g), SceneManager::SceneMode::ADDITIVE);
}

void LocationsScene::update() {
	for (int i = 0; i < locations.size(); i++) {
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

		if (Collisions::collides(mousePos, 1, 1, buttonTr->getPos(), buttonTr->getW(), buttonTr->getH())) {
			if (!ih().getMouseButtonState(InputHandler::LEFT)) {
				if (!mouseClick) {
					infos[i]->setActive(true);
				}
			}
			return;
		}
		else
		{
			infos[i]->setActive(false);
		}


	}
}

