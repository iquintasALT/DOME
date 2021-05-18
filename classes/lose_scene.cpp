#include "lose_scene.h"
#include "../classes/locations_scene.h"
#include "../classes/menu_scene.h"
#include "../game/Game.h"
#include "../classes/settings_scene.h"

LoseScene::LoseScene(Game* game, WAYSTODIE opcion, bool state) : GameScene(game, "Menu")
{
	auto menuButton = new PauseButton(Vector2D(consts::WINDOW_WIDTH / 2 - 128, 530), Vector2D(256, 64), &sdlutils().images().at("mainmenuButton"), backToMenu, g_, mngr_);
	mngr_->addEntity(menuButton);
	if (!state)
	{
		back = &sdlutils().images().at("lose");
	}
	else
	{
		back = &sdlutils().images().at("win");//Si ganas, cambiar el sprite
	}
	string text;
	switch (opcion)
	{
	case WAYSTODIE::DAYS:
		text = "YOU SHOULD END THE GAME SOONER";
		break;
	case WAYSTODIE::COLD:
		text = "YOU SHOULD EXIT THE RAID BEFORE THE TIME'S GONE";
		break;
	case WAYSTODIE::HUNGER:
		text = "YOU SHOULD EAT, IT'S IMPORTANT :)";
		break;
	case WAYSTODIE::BLEED:
		text = "YOU SHOULD TRY TO FIND ITEMS TO STOP BLEEDING";
		break;
	case WAYSTODIE::INTOXICATION:
		text = "YOU SHOULD TRY TO FIND SOMETHING TO DETOXIFY";
		break;
	case WAYSTODIE::PAIN:
		text = "YOU SHOULD TRY TO FIND SOMETHING, SOME PAINKILLER";
		break;
	case WAYSTODIE::CONTUSION:
		text = "CAREFUL WITH THE HEIGHTS";
		break;
	default:
		text = " ";
		break;
	}
	advice = new Texture(sdlutils().renderer(), text, sdlutils().fonts().at("OrbitronRegular"),
		build_sdlcolor(0xffffffff));
}


void LoseScene::backToMenu(Manager* mngr) {
	ih().clearState();
	mngr->getGame()->numDays = 0;

	mngr->ChangeScene(new MenuScene(mngr->getGame(), false), SceneManager::SceneMode::SINGLE);
}

void LoseScene::render() {
	SDL_Rect rect = { 0, 0, consts::WINDOW_WIDTH, consts::WINDOW_HEIGHT };
	back->render(rect);
	advice->render(consts::WINDOW_WIDTH/2-advice->width()/2,consts::WINDOW_HEIGHT-consts::WINDOW_HEIGHT/2);
	GameScene::render();
}

LoseScene::~LoseScene() {
	delete advice;
}