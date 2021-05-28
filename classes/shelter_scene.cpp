#include "locations_scene.h"

#include "../game/Game.h"

#include "../classes/shelter_scene.h"
#include "../classes/pause_scene.h"
#include "../classes/shelter_hud.h"
#include "../classes/lose_scene.h"

#include "../components/open_station.h"
#include "../components/hunger_component.h"
#include "../components/tiredness_component.h"

#include <memory>

#include "../classes/player.h"

using std::cout;
using std::cerr;
using std::endl;

#undef main

void ShelterScene::init() {
	mngr_->getGame()->currentScene = SCENES::SHELTER;

	string path_ = "./resources/tilemap/zona_shelter.tmx";
	loadMap(path_);

	Player* player = static_cast<Player*>(mngr_->getHandler<Player_hdlr>());

	auto weapon = player->getWeapon();
	if (weapon->isActive())
		weapon->setActive(false);

	player->getComponent<HungerComponent>()->decreaseHunger(0.5);
	player->getComponent<TirednessComponent>()->decreaseTiredness(0.5);

	auto shelterHud = new ShelterHud(mngr_, this);

	createParallaxBackground(5);

	uselessMngr = new Manager(g_);
	craftSys = new CraftingSystem(mngr_);

	spaceshipStation = new SpaceshipStation(mngr_, uselessMngr, craftSys, this);
	Entity* spaceshipImg = mngr_->addEntity();
	spaceshipImg->addComponent<Transform>(Vector2D{ spaceshipStPos.getX(),spaceshipStPos.getY() }, spaceshipStSize.getX(), spaceshipStSize.getY(), 0);
	spaceshipImg->addComponent<Image>(&sdlutils().images().at("rocket"), 1, 1, 0, 0);
	spaceshipImg->addComponent<OpenStation>(spaceshipStation);
	mngr_->addRenderLayer<Background>(spaceshipImg);
	
	medical_Workshop = new Workshop(mngr_, uselessMngr, craftSys, this);
	medical_Workshop->setWorkshopItems(vector<ITEMS>{ANTIDOTE, BANDAGE, SPLINT, PAINKILLER, FOOD});
	Entity* medImg = mngr_->addEntity();
	medImg->addComponent<Transform>(Vector2D{ medPos.getX(),medPos.getY() }, medSize.getX(), medSize.getY(), 0);
	medImg->addComponent<OpenStation>(medical_Workshop);
	mngr_->addRenderLayer<Background>(medImg);

	sleep_Station = new SleepStation(mngr_, uselessMngr, this);
	sleepImg = mngr_->addEntity();
	sleepImg->addComponent<Transform>(Vector2D{ sleepStPos.getX()  ,sleepStPos.getY() }, sleepStSize.getX(), sleepStSize.getY(), 0);
	sleepImg->addComponent<OpenStation>(sleep_Station);
	mngr_->addRenderLayer<Background>(sleepImg);

	mechanical_Workshop = new Workshop(mngr_, uselessMngr, craftSys, this);
	mechanical_Workshop->setWorkshopItems(vector<ITEMS>{METAL_PLATES, WEAPON_UPGRADE, CLASSIC_AMMO, LASER_AMMO, RICOCHET_AMMO});
	Entity* mechImg = mngr_->addEntity();
	mechImg->addComponent<Transform>(Vector2D{ mechPos.getX(),mechPos.getY() }, mechSize.getX(), mechSize.getY(), 0);
	mechImg->addComponent<OpenStation>(mechanical_Workshop);
	mngr_->addRenderLayer<Background>(mechImg);
}

void ShelterScene::update() {
	mngr_->update();

	if (spaceshipStation->isBuilt())mngr_->ChangeScene(new LoseScene(mngr_->getGame(), WAYSTODIE::NONE, true), SceneManager::SceneMode::ADDITIVE);

	if (ih().keyDownEvent() && ih().isKeyDown(SDL_SCANCODE_ESCAPE)) {
		mngr_->getGame()->setShouldRenderFPS(false);
		mngr_->ChangeScene(new PauseScene(mngr_->getGame()), SceneManager::SceneMode::ADDITIVE);
	}
}

void ShelterScene::render()
{
	mngr_->render();
}

void ShelterScene::sleepTransition()
{
	//funcion llamada al terminar la transicion
	std::function<void()> goToLocationsScene([this] { mngr_->ChangeScene(nullptr, SceneManager::SceneMode::REMOVE); });
	//se desactivan el toolTip, la estacion, y su componente para abrirla
	sleep_Station->setActive(false);
	sleepInteractable->getComponent<InteractableElement>()->setToolTipActive(false);
	sleepImg->getComponent<OpenStation>()->enabled = false;
	static_cast<Player*>(mngr_->getHandler<Player_hdlr>())->getWeapon()->getInv()->enabled = false;
	//se desactiva el movimiento mientras se duerme
	mngr_->getHandler<Player_hdlr>()->getComponent<KeyboardPlayerCtrl>()->enabled = false;
	mngr_->getHandler<Player_hdlr>()->getComponent<RigidBody>()->setVel(Vector2D{ 0,0 });
	createTransition(3.0, false, goToLocationsScene, ". . . Z Z Z");
	//se reajusta la escala de la camara
	Camera::mainCamera->restoreScale();
}

void ShelterScene::useActions(int numActions)
{
	if (actions - numActions >= 0) actions -= numActions;
}

void ShelterScene::addAction()
{
	actions++;
}

void ShelterScene::createParallaxBackground(int numOfRep) {
	createParallaxLayer(0, &sdlutils().images().at("skyS"), numOfRep);
	createParallaxLayer(0.2, &sdlutils().images().at("ruins"), numOfRep);
	createParallaxLayer(0.3, &sdlutils().images().at("houses2S"), numOfRep);
	createParallaxLayer(0.4, &sdlutils().images().at("houses1S"), numOfRep);
	createParallaxLayer(0.5, &sdlutils().images().at("houses3S"), numOfRep);
	createParallaxLayer(0.6, &sdlutils().images().at("roadS"), numOfRep);
	createParallaxLayer(0.7, &sdlutils().images().at("fence"), numOfRep);
}