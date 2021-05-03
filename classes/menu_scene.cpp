#include "menu_scene.h"
#include "shelter_scene.h"
#include "raid_scene.h"
#include "../sdlutils/SDLUtils.h"
#include "../game/Game.h"
#include "locations_scene.h"
#include "../ecs/Manager.h"

MenuScene::MenuScene(Game* game) :GameScene(game, "Menu") {

	auto* aux = new MenuButton(Vector2D(sdlutils().height()/2 + 100, sdlutils().width() / 2  -200) , Vector2D(100, 100),
		&sdlutils().images().at("shelterButton"), playGame, g_, mngr_);
	mngr_->addEntity(aux);
	//mngr_->addRenderLayer<Enemy>(aux);

	aux = new MenuButton(Vector2D(sdlutils().height() / 2 + +300, sdlutils().width() / 2 - 200), Vector2D(100, 100),
		&sdlutils().images().at("raidButton"), setting, g_, mngr_);
	mngr_->addEntity(aux);
	//mngr_->addRenderLayer<Enemy>(aux);

	aux = new MenuButton(Vector2D(sdlutils().height() / 2  - 100, sdlutils().width() / 2 - 200), Vector2D(100, 100),
		&sdlutils().images().at("raidButton"), exit, g_, mngr_);
	mngr_->addEntity(aux);
	//mngr_->addRenderLayer<Enemy>(aux);

	back = &sdlutils().images().at("dclock");

	//soundManager().playMusic("imperial");
}

void MenuScene::init() {}

void MenuScene::render()
{
	back->render(0,0);
	GameScene::render();
}

void MenuScene::playGame(Manager* mngr) {
	mngr->ChangeScene(new LocationsScene(mngr->getGame()), SceneManager::SceneMode::ADDITIVE);
}

void MenuScene::setting(Manager* mngr) {/*
	g->getStateMachine()->pushState(new RaidScene("./resources/tilemap/template.tmx", "template", g));
	g->getStateMachine()->currentState()->init();*/
}

void MenuScene::exit(Manager* mngr) {
	mngr->getGame()->quitGame();
}

MenuScene::~MenuScene()
{
	//delete back;
}