#include "../classes/shelter_scene.h"
#include "../components/hunger_component.h"
#include "../components/tiredness_component.h"
#include "../game/Game.h"
#include "locations_scene.h"
#include "../classes/pause_scene.h"
#include "../components/open_station.h"
#include "../classes/shelter_hud.h"
#include "../classes/lose_scene.h"

#include <memory>

//#if defined(_WIN32)
//#include <windows.h>
//#endif
//#include <iostream>

using std::cout;
using std::cerr;
using std::endl;

#undef main

void ShelterScene::init() {
	mngr_->getGame()->currentScene = SCENES::SHELTER;

	string path_ = "./resources/tilemap/zona_shelter.tmx";
	loadMap(path_);

	Player* player = dynamic_cast<Player*>(mngr_->getHandler<Player_hdlr>());

	auto shelterHud = new ShelterHud(mngr_, this);

	auto weapon = player->getCurrentWeapon();

	createParallaxBackground(5);

	if (weapon->isActive())
		weapon->setActive(false);

	uselessMngr = new Manager(g_);
	craftSys = new CraftingSystem(mngr_);

	spaceshipStation = new SpaceshipStation(mngr_, uselessMngr, craftSys, this);
	Entity* spaceshipImg = mngr_->addEntity();
	spaceshipImg->addComponent<Transform>(Vector2D{ spaceshipStPos.getX(),spaceshipStPos.getY() }, spaceshipStSize.getX(), spaceshipStSize.getY(), 0);
	spaceshipImg->addComponent<Image>(&sdlutils().images().at("rocket"), 1, 1, 0, 0);
	spaceshipImg->addComponent<Open_station>(spaceshipStation);
	mngr_->addRenderLayer<Background>(spaceshipImg);

	medical_Workshop = new Workshop(mngr_, uselessMngr, craftSys, this);
	medical_Workshop->setWorkshopItems(vector<ITEMS>{ANTIDOTE, BANDAGE, SPLINT});
	Entity* medImg = mngr_->addEntity();
	medImg->addComponent<Transform>(Vector2D{ medPos.getX(),medPos.getY() }, medSize.getX(), medSize.getY(), 0);
	medImg->addComponent<Open_station>(medical_Workshop);
	mngr_->addRenderLayer<Background>(medImg);

	sleep_Station = new SleepStation(mngr_, uselessMngr, this);
	Entity* sleepImg = mngr_->addEntity();
	sleepImg->addComponent<Transform>(Vector2D{ sleepStPos.getX()  ,sleepStPos.getY() }, sleepStSize.getX(), sleepStSize.getY(), 0);
	sleepImg->addComponent<Open_station>(sleep_Station);
	mngr_->addRenderLayer<Background>(sleepImg);

	mechanical_Workshop = new Workshop(mngr_, uselessMngr, craftSys, this);
	mechanical_Workshop->setWorkshopItems(vector<ITEMS>{METAL_PLATES, WEAPON_UPGRADE, CLASSIC_AMMO, SPLINT});
	Entity* mechImg = mngr_->addEntity();
	mechImg->addComponent<Transform>(Vector2D{ mechPos.getX(),mechPos.getY() }, mechSize.getX(), mechSize.getY(), 0);
	mechImg->addComponent<Open_station>(mechanical_Workshop);
	mngr_->addRenderLayer<Background>(mechImg);
}

void ShelterScene::update() {
	mngr_->update();

	if (spaceshipStation->isBuilt())mngr_->ChangeScene(new LoseScene(mngr_->getGame(), WAYSTODIE::NONE, true), SceneManager::SceneMode::ADDITIVE);

	/*mechanical_Workshop->update();
	medical_Workshop->update();
	sleep_Station->update();*/

	if (ih().keyDownEvent() && ih().isKeyDown(SDL_SCANCODE_ESCAPE)) {
		mngr_->getGame()->setFPSActive(false);
		mngr_->ChangeScene(new PauseScene(mngr_->getGame()), SceneManager::SceneMode::ADDITIVE);
	}
}

void ShelterScene::render()
{
	mngr_->render();

	/*mechanical_Workshop->render();
	medical_Workshop->render();
	sleep_Station->render();*/
}

void ShelterScene::useAction()
{
	if (actions > 0) actions--;
	std::cout << "actions: " << actions << endl;
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




