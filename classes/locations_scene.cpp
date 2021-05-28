#include "locations_scene.h"

#include "../ecs/Component.h"

#include "../game/Game.h"
#include "../game/constant_variables.h"

#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/SoundManager.h"

#include "../components/image.h"
#include "../components/tiredness_component.h"
#include "../components/particle_system.h"

#include "../classes/raid_scene.h"
#include "../classes/camera.h"

void LocationsScene::init()
{
	Vector2D a;
	Camera::mainCamera->Move(a);

	addBackground(&sdlutils().images().at("bgImage5"));
	addBackground(&sdlutils().images().at("bgImage4"));
	addBackground(&sdlutils().images().at("bgImage6"));
	addBackground(&sdlutils().images().at("bgImage2"));
	addBackground(&sdlutils().images().at("bgImage7"));

	auto background = mngr_->addEntity();
	background->addComponent<Transform>(Vector2D(sdlutils().width() * 0.33 , 0),
		sdlutils().height(), sdlutils().height());
	background->addComponent<Image>(&sdlutils().images().at("location_image"), 1, 3, 0, 0, true);
	mngr_->addRenderLayer<Background>(background);

	addInfoText(&sdlutils().images().at("info_nuclear"), Vector2D(50, 0), 280, 630);
	addInfoText(&sdlutils().images().at("info_supermercado"), Vector2D(50, 0), 280, 630); 
	addInfoText(&sdlutils().images().at("info_comunicaciones"), Vector2D(50, 0), 280, 630); 
	addInfoText(&sdlutils().images().at("info_hospital"), Vector2D(50, 0), 280, 630); 
	addInfoText(&sdlutils().images().at("info_shop"), Vector2D(50, 0), 280, 630); 

	loadLocationButtons(consts::NUM_LOCATIONS);
	mouseOverInfo = vector<bool>(locations.size(), false);

	addFocus();
	addTravelLine();
	addTravelLineAnimation();
	addParticles();
}

void LocationsScene::onLoad()
{
	name = "Day " + std::to_string(getGame()->numDays) + " out of " + std::to_string(consts::MAX_DAYS);
	createTransition(3.5);
}


void LocationsScene::loadLocationButtons(int buttons) {
	buttonPositions = vector<Transform*>(buttons);
	locations = vector<Entity*>(buttons);

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
			if (obj.getName() == "shelter") {
				shelterImg = mngr_->addEntity();
				shelterImg->addComponent<Transform>(Vector2D(aabb.left, aabb.top), 75, 75);
				shelterImg->addComponent<Image>(&sdlutils().images().at("location_icons"), 2, 3, 1, 2, true);
				mngr_->addRenderLayer<Interface>(shelterImg);
			}
			else {
				auto col = obj.getProperties()[0].getIntValue();
				auto index = obj.getProperties()[1].getIntValue();
				auto row = obj.getProperties()[2].getIntValue();

				auto button = mngr_->addEntity();
				auto tr = button->addComponent<Transform>(Vector2D(aabb.left, aabb.top), 75, 75);
				buttonPositions[index] = tr;
				button->addComponent<Image>(&sdlutils().images().at("location_icons"), 2, 3, row, col, true);
				mngr_->addRenderLayer<Interface>(button);
				locations[index] = button;
			}
		}
	}
}

void LocationsScene::changeToRaid(Game* g, int index) {
	g->playerSavedData->updateTiredness(consts::TIREDNESS_FROM_TRAVELING[index]);
	g->currentScene = (SCENES)index;
	g->setShouldRenderFPS(true);
	soundManager().playSFX("push_button");
	mngr_->ChangeScene(new RaidScene(paths[index], names[index], g), SceneManager::SceneMode::ADDITIVE);
}

void LocationsScene::update() {
	mngr_->update();
	playTravelLineAnimation();

	for (int i = 0; i < locations.size(); i++) {
		Vector2D mousePos(ih().getMousePos().first, ih().getMousePos().second);
		auto buttonTr = locations[i]->getComponent<Transform>();

		if (ih().getMouseButtonState(InputHandler::LEFT)) {
			if (!mouseClick) {
				if (Collisions::collides(mousePos, 1, 1, buttonTr->getPos(), buttonTr->getW(), buttonTr->getH())) {
					changeToRaid(g_, i);
					
					mouseClick = true;
					soundManager().playSFX("push_button");
					return;
				}
			}
		}
		else if (mouseClick) mouseClick = false;

		
		if (Collisions::collides(mousePos, 1, 1, buttonTr->getPos(), buttonTr->getW(), buttonTr->getH())) { //Si estas encima
			if (!ih().getMouseButtonState(InputHandler::LEFT)) {
				if (!mouseClick) {
					if (!mouseOverInfo[i]) {
						mouseOverInfo[i] = true;

						//Foco
						setFocus(buttonPositions[i]->getPos());
						setTravelLine(buttonPositions[i]);
						focus->getComponent<Image>()->changeFrame(0, 0);
						if (i != lastBackGroundActive) {
							updateAnimation();
							infos[lastBackGroundActive]->setActive(false);
							backgrounds[lastBackGroundActive]->setActive(false);
							infos[i]->setActive(true);
							backgrounds[i]->setActive(true);
							soundManager().playSFX("over_button");

							return;
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
	initFocus();
}

void LocationsScene::setFocus(Vector2D position) {
	focus->getComponent<Transform>()->setPos(position);
}

void LocationsScene::initFocus() {
	//Se establece el foco al principio en uno cualquiera
	setFocus(buttonPositions[3]->getPos());
	infos[3]->setActive(true);

	//Se activa el fondo correspondiente al boton con el foco
	backgrounds[3]->setActive(true); 
	focus->getComponent<Image>()->changeFrame(0, 0);
	lastBackGroundActive = 3;
}

void LocationsScene::addTravelLine() {
	travelLine = mngr_->addEntity();
	travelLine->addComponent<Transform>(Vector2D(0, 0), 10, 10);
	travelLine->addComponent<Image>(&sdlutils().images().at("travelLine"), true);
	mngr_->addRenderLayer<Background>(travelLine);

	setTravelLine(buttonPositions[3]);
}

void LocationsScene::setTravelLine(Transform* buttonTr) {
	auto travelLineTr = travelLine->getComponent<Transform>();
	auto shelterImgTr = shelterImg->getComponent<Transform>();

	//Centro de la imagenes
	auto buttonCenterPos = buttonTr->getCenterPos();
	auto shelterImgCenterPos = shelterImgTr->getCenterPos();

	Vector2D dir = buttonCenterPos - shelterImgCenterPos;
	travelLineTr->setW(dir.magnitude());

	//Punto medio entre la linea imaginaria que une los dos botones
	int linePosX = abs(shelterImgCenterPos.getX() + buttonCenterPos.getX()) / 2;
	int linePosY = abs(shelterImgCenterPos.getY() + buttonCenterPos.getY()) / 2;

	travelLineTr->setPos(Vector2D(linePosX-travelLineTr->getW()/2, linePosY-travelLineTr->getH()/2));
	travelLineTr->setRot(Vector2D(1, 0).angle(dir.normalize()));
}

void LocationsScene::addTravelLineAnimation() {
	auto centerImg = shelterImg->getComponent<Transform>()->getCenterPos();

	travelLineAnimation = mngr_->addEntity();
	auto tr = travelLineAnimation->addComponent<Transform>(Vector2D(), 20, 10);
	tr->setRot(travelLine->getComponent<Transform>()->getRot());
	tr->setCenterPos(centerImg);

	travelLineAnimation->addComponent<Image>(&sdlutils().images().at("travelLineAnimation"), true);
	mngr_->addRenderLayer<Background>(travelLineAnimation);
}

void LocationsScene::playTravelLineAnimation() {
	auto tr = travelLineAnimation->getComponent<Transform>();

	auto focusCenterPos = focus->getComponent<Transform>()->getCenterPos();
	auto shelterImgCenterPos = shelterImg->getComponent<Transform>()->getCenterPos();
	auto dir = focusCenterPos - shelterImgCenterPos;

	auto focusPosition = focus->getComponent<Transform>()->getPos();

	tr->setPos(tr->getPos() + dir.normalize() * animationSpeed);

	if ((tr->getCenterPos()-focusCenterPos).magnitude() <= 5) tr->setCenterPos(shelterImgCenterPos);
}

void LocationsScene::updateAnimation() {
	auto tr = travelLineAnimation->getComponent<Transform>();
	auto shelterImgTr = shelterImg->getComponent<Transform>();
	auto centerPos = shelterImg->getComponent<Transform>()->getCenterPos();
	tr->setCenterPos(centerPos);
	tr->setRot(travelLine->getComponent<Transform>()->getRot());
}

void LocationsScene::addParticles()
{
	auto shelterTr = shelterImg->getComponent<Transform>();
	particles = mngr_->addEntity();
	mngr_->addRenderLayer<ULTIMATE>(particles);
	auto pos = Camera::mainCamera->WorldToPointSpace(shelterTr->getPos());
	particles->addComponent<Transform>(
		pos);
	auto p = particles->addComponent<ParticleSystem>(
		&sdlutils().images().at("donut"), 1, 1, 0, 0);

	p->emitting = true;
	p->rateOverTime = 1;
	p->lifeTime = 0.8;
	p->destroyAfterTime = false;
	p->particleScale = 3;
	p->sizeOverTime = true;
	p->sizeCurve = ParticleSystem::Function(0.7, 0);
	p->distanceToOrigin = 0;
	p->speed = 0;
	p->dir = Vector2D();
	p->burst = false;
	p->centerAlign = true;
	p->gravity = false;
}
