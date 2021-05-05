#include "lose_scene.h"
#include "../classes/locations_scene.h"
#include "../classes/menu_scene.h"
#include "../game/Game.h"
#include "../classes/settings_scene.h"

Lose_scene::Lose_scene(Game* game, muertes opcion):GameScene(game, "Menu")
{
	auto* aux = new MenuButton(Vector2D(sdlutils().height() / 2 + 100, sdlutils().width() / 2 - 200), Vector2D(200, 100),
		&sdlutils().images().at("raidButton"), GoBackMenu, g_, mngr_);
	mngr_->addEntity(aux);


	back = &sdlutils().images().at("lose"); 
	string text;
	switch (opcion)
	{
	case dias:
		text = "Te recomendamos que intentes acabar el juego en menos tiempo";
		break;
	case frio:
		text = "Te recomendamos que salgas de la raid antes de que se acabe el tiempo";
		break;
	case comida:
		text = "Te recomendamos que comas, es importante :)";
		break;
	case desangrado:
		text = "Te recomendamos que busques formas de curarte en el mapa";
		break;
	default:
		text = "Esto no deberia salir";
		break;
	}

	advice = new Texture(sdlutils().renderer(), text, sdlutils().fonts().at("OrbitronRegular"),
		build_sdlcolor(0xffffffff));
}


void Lose_scene::GoBackMenu(Manager* mngr)
{
	ih().clearState();
	mngr->ChangeScene(new MenuScene(mngr->getGame()), SceneManager::SceneMode::SINGLE);
	mngr->getGame()->currentScene = SCENES::MAINMENU;
}

void Lose_scene::render()
{
	back->render(0, 0);

	advice->render(100,200);

	GameScene::render();
}

Lose_scene::~Lose_scene()
{
	delete advice;
}