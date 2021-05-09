#include "locations_scene.h"
#include "../game/Game.h"
#include "../classes/raid_scene.h"
#include "../sdlutils/Texture.h"
#include "../components/Image.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Component.h"

void LocationsScene::init()
{
	addBackground(&sdlutils().images().at("bgImage7"));
	addBackground(&sdlutils().images().at("bgImage5"));
	addBackground(&sdlutils().images().at("bgImage2"));
	addBackground(&sdlutils().images().at("bgImage6"));
	addBackground(&sdlutils().images().at("bgImage4"));

	auto background = mngr_->addEntity();
	background->addComponent<Transform>(Vector2D(sdlutils().width() * 0.33 , 0),
		sdlutils().height(), sdlutils().height());
	background->addComponent<Image>(&sdlutils().images().at("location_image"), 1, 3, 0, 0, true);
	mngr_->addRenderLayer<Background>(background);

	addInfoText(&sdlutils().images().at("info_shop"), Vector2D(50, 0), 280, 630); 
	addInfoText(&sdlutils().images().at("info_nuclear"), Vector2D(50, 0), 280, 630); 
	addInfoText(&sdlutils().images().at("info_hospital"), Vector2D(50, 0), 280, 630); 
	addInfoText(&sdlutils().images().at("info_comunicaciones"), Vector2D(50, 0), 280, 630); 
	addInfoText(&sdlutils().images().at("info_supermercado"), Vector2D(50, 0), 280, 630); 

	addFocus();

	loadLocationButtons();
	mouseOverInfo = vector<bool>(locations.size(), false);

	initFocus();

	name = "Day " + std::to_string(getGame()->numDays) + " out of " + std::to_string(consts::MAX_DAYS);
	//createTransition();
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
			auto tr = button->addComponent<Transform>(Vector2D(aabb.left, aabb.top), 75, 75);
			buttonPositions.push_back(tr);
			button->addComponent<Image>(&sdlutils().images().at("location_icons"), 2, 3, row, col, true);
			mngr_->addRenderLayer<Background>(button);
			locations.push_back(button);
		}
	}
}

void LocationsScene::changeToRaid(Game* g, int index) {
	g->currentScene = scenes[index];
	mngr_->ChangeScene(new RaidScene(paths[index], names[index], g), SceneManager::SceneMode::ADDITIVE);
}

void LocationsScene::update() {
	for (int i = 0; i < locations.size(); i++) {
		Vector2D mousePos(ih().getMousePos().first, ih().getMousePos().second);
		auto buttonTr = locations[i]->getComponent<Transform>();

		if (ih().getMouseButtonState(InputHandler::LEFT)) {
			if (!mouseClick) {
				if (Collisions::collides(mousePos, 1, 1, buttonTr->getPos(), buttonTr->getW(), buttonTr->getH())) {
					changeToRaid(g_, i);
					
					mouseClick = true;
					return;
				}
			}
		}
		else if (mouseClick) mouseClick = false;

		
		if (Collisions::collides(mousePos, 1, 1, buttonTr->getPos(), buttonTr->getW(), buttonTr->getH())) {
			if (!ih().getMouseButtonState(InputHandler::LEFT)) {
				if (!mouseClick) {
					if (!mouseOverInfo[i]) {
						mouseOverInfo[i] = true;
						//Foco
						setFocus(buttonPositions[i]->getPos());
						focus->getComponent<Image>()->changeFrame(0, 0);
						if (i != lastBackGroundActive) {
							infos[lastBackGroundActive]->setActive(false);
							backgrounds[lastBackGroundActive]->setActive(false);

							infos[i]->setActive(true);
							backgrounds[i]->setActive(true);
						}
					}
				}
			}
		}
		else {
			if (mouseOverInfo[i]) {
				lastBackGroundActive = i;
				mouseOverInfo[i] = false;
			}
		}
	}
}

void LocationsScene::addInfoText(Texture* t, Vector2D pos, int xSize, int ySize) {
	auto info = mngr_->addEntity();
	info->addComponent<Transform>(pos, xSize, ySize);
	info->addComponent<Image>(t, 1, 1, 0, 0, true);
	info->setActive(false);
	mngr_->addRenderLayer<Item>(info);
	infos.push_back(info);
}

void LocationsScene::addBackground(Texture* t) {
	auto background = mngr_->addEntity();
	background->addComponent<Transform>(Vector2D(0, 0), sdlutils().width(), sdlutils().height());
	background->addComponent<Image>(t, 1, 1, 0, 0, true);
	background->setActive(false);
	mngr_->addRenderLayer<Background>(background);
	backgrounds.push_back(background);
}
void LocationsScene::addFocus() {
	focus = mngr_->addEntity();
	focus->addComponent<Transform>(Vector2D(100, 100), 75, 75);
	focus->addComponent<Image>(&sdlutils().images().at("locationButtonFocus"), 1, 2, 32, 32, true);
	mngr_->addRenderLayer<Interface>(focus);
}

void LocationsScene::setFocus(Vector2D position) {
	focus->getComponent<Transform>()->setPos(position);
}

void LocationsScene::initFocus() {
	setFocus(buttonPositions[0]->getPos()); //Se establece el foco al principio en uno cualquiera
	infos[0]->setActive(true);
	backgrounds[0]->setActive(true); //Se activa el fondo correspondiente al boton con el foco
	focus->getComponent<Image>()->changeFrame(0, 0);
	lastBackGroundActive = 0;
}


//FADE

Fade::Fade(float speed) : tr_(nullptr) {
	t = 0;
	f = 255;
	done = false;
	speed_ = speed;
	black_ = &sdlutils().images().at("black");
}

void Fade::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);
}

void Fade::update() {
	if (!done) {
		t += consts::DELTA_TIME * speed_;

		const float fade = 0.2f;

		if (t < fade)
		f = (fade - t) / fade * 255;

		if (f < 10) done = true;
	}
}

void Fade::render(){
	black_->setAlpha(f);
	black_->render({ 0,0, sdlutils().width(), sdlutils().height() });
}

void Fade::setAlpha(float alpha) {
	f = alpha;
}
