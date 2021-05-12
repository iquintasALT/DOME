#include "controls_scene.h"
#include "pause_button.h"
#include "menu_button.h"
#include "../sdlutils/SDLUtils.h"
#include "../game/constant_variables.h"
#include "locations_scene.h"

void ControlsScene::init()
{
	auto playButton = new PauseButton(Vector2D(0, 0), Vector2D(consts::WINDOW_WIDTH,consts::WINDOW_HEIGHT), &sdlutils().images().at("controls"), goGame, g_, mngr_, 0, " ");
	mngr_->addEntity(playButton);
}	


void ControlsScene::goGame(Manager* mngr)
{
	ih().clearState();
	mngr->ChangeScene(new LocationsScene(mngr->getGame()), SceneManager::SceneMode::ADDITIVE);
}