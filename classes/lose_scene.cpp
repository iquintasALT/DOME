#include "lose_scene.h"
#include "../classes/locations_scene.h"
#include "../classes/menu_scene.h"
#include "../game/Game.h"
#include "../classes/settings_scene.h"

LoseScene::LoseScene(Game* game, WAYSTODIE opcion) : GameScene(game, "Menu")
{
	auto menuButton = new PauseButton(Vector2D(consts::WINDOW_WIDTH / 2 - 128, 530), Vector2D(256, 64), &sdlutils().images().at("mainmenuButton"), backToMenu, g_, mngr_);
	mngr_->addEntity(menuButton);

	back = &sdlutils().images().at("lose"); 
	string text;
	switch (opcion)
	{
	case DAYS:
		text = "YOU SHOULD END THE GAME SOONER";
		break;
	case COLD:
		text = "YOU SHOULD EXIT THE RAID BEFORE THE TIME'S GONE";
		break;
	case HUNGER:
		text = "YOU SHOULD EAT, IT'S IMPORTANT :)";
		break;
	case BLEED:
		text = "YOU SHOULD TRY TO FIND ITEMS TO STOP BLEEDING";
		break;
	case INTOXICATION:
		text = "PRINGAO";
		break;
	case PAIN:
		text = "PRINGAO";
		break;
	case CONTUSION:
		text = "PRINGAO";
		break;
	default:
		text = "THIS SHOULD NOT APPEAR";
		break;
	}
	advice = new Texture(sdlutils().renderer(), text, sdlutils().fonts().at("OrbitronRegular"),
		build_sdlcolor(0xffffffff));
}


void LoseScene::backToMenu(Manager* mngr) {
	ih().clearState();
	mngr->ChangeScene(new MenuScene(mngr->getGame()), SceneManager::SceneMode::SINGLE);
}

void LoseScene::render() {
	back->render(0, 0);
	advice->render(100,300);
	GameScene::render();
}

LoseScene::~LoseScene() {
	delete advice;
}