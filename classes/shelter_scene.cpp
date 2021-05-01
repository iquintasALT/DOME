#include "../classes/shelter_scene.h"
#include "../components/hunger_component.h"
#include "../components/tiredness_component.h"
#include "../game/Game.h"
#include "locations_scene.h"
#include "../classes/pause_scene.h"
#include "../components/open_station.h"

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
	string path_ = "./resources/tilemap/zona_shelter.tmx";
	loadMap(path_);
	Player* player = dynamic_cast<Player*>(mngr_->getHandler<Player_hdlr>());
	craftSys = new CraftingSystem(mngr_);

	uselessMngr = new Manager(g_);

	Vector2D auxPos = player->getComponent<Transform>()->getPos();

	mechanical_Workshop = new Workshop(mngr_, uselessMngr, craftSys);
	mechanical_Workshop->setWorkshopItems(vector<ITEMS>{METAL_PLATES, WEAPON_UPGRADE, CLASSIC_AMMO, BACKPACK_UPGRADE, ARMOUR_UPGRADE });
	Entity* mechImg = mngr_->addEntity();
	mechImg->addComponent<Transform>(Vector2D{ auxPos.getX() ,auxPos.getY() }, 50, 50, 0);
	mechImg->addComponent<Image>(&sdlutils().images().at("wardrobe"), 7, 2, 3, 0);
	mechImg->addComponent<Open_station>(mechanical_Workshop);
	mngr_->addRenderLayer<Background>(mechImg);


	medical_Workshop = new Workshop(mngr_, uselessMngr, craftSys);
	medical_Workshop->setWorkshopItems(vector<ITEMS>{ANTIDOTE, BANDAGE, SPLINT});
	Entity* medImg = mngr_->addEntity();
	medImg->addComponent<Transform>(Vector2D{ auxPos.getX() - 100,auxPos.getY() }, 50, 50, 0);
	medImg->addComponent<Image>(&sdlutils().images().at("wardrobe"), 7, 2, 6, 0);
 	medImg->addComponent<Open_station>(medical_Workshop);
	mngr_->addRenderLayer<Background>(medImg);

	sleep_Station = new SleepStation(mngr_, uselessMngr);
	Entity* sleepImg = mngr_->addEntity();
	sleepImg->addComponent<Transform>(Vector2D{ auxPos.getX() - 200 ,auxPos.getY() }, 50, 50, 0);
	sleepImg->addComponent<Image>(&sdlutils().images().at("wardrobe"), 7, 2, 4, 0);
	sleepImg->addComponent<Open_station>(sleep_Station);
	mngr_->addRenderLayer<Background>(sleepImg);
}



void ShelterScene::update() {
	mngr_->update();

	/*mechanical_Workshop->update();
	medical_Workshop->update();
	sleep_Station->update();*/

	if (ih().keyDownEvent() && ih().isKeyDown(SDL_SCANCODE_ESCAPE)) {
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



