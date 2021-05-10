#include "lore_scene.h"
#include "../game/constant_variables.h"
#include "locations_scene.h"


void LoreScene::init()
{

}


void LoreScene::update()
{

}


void LoreScene::StartGame(Manager* mngr)
{
	ih().clearState();
	mngr->ChangeScene(new LocationsScene(mngr->getGame()), SceneManager::SceneMode::ADDITIVE);
}