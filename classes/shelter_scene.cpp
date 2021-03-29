#include "../classes/shelter_scene.h"
#include "../components/hunger_component.h"
#include "../components/tiredness_component.h"

#include <sdlgui/window.h>
#include <sdlgui/layout.h>
#include <sdlgui/label.h>
#include <sdlgui/checkbox.h>
#include <sdlgui/button.h>
#include <sdlgui/toolbutton.h>
#include <sdlgui/popupbutton.h>
#include <sdlgui/combobox.h>
#include <sdlgui/dropdownbox.h>
#include <sdlgui/progressbar.h>
#include <sdlgui/entypo.h>
#include <sdlgui/messagedialog.h>
#include <sdlgui/textbox.h>
#include <sdlgui/slider.h>
#include <sdlgui/imagepanel.h>
#include <sdlgui/imageview.h>
#include <sdlgui/vscrollpanel.h>
#include <sdlgui/colorwheel.h>
#include <sdlgui/graph.h>
#include <sdlgui/tabwidget.h>
#include <sdlgui/switchbox.h>
#include <sdlgui/formhelper.h>
#include <memory>

//#if defined(_WIN32)
//#include <windows.h>
//#endif
//#include <iostream>



using std::cout;
using std::cerr;
using std::endl;

#undef main

using namespace sdlgui;

void ShelterScene::init() {
	Entity* player = mngr_->addEntity();
	auto tr = player->addComponent<Transform>(Vector2D(), Vector2D(), 32, 64, 0);
	player->addComponent<Image>(&sdlutils().images().at("player"), 3, 14, 0, 0);
	player->addComponent<ParticleSystem>(&sdlutils().images().at("dust"), 1, 1, 0, 0);
	player->addComponent<GravityComponent>();
	player->addComponent<KeyboardPlayerCtrl>();
	player->addComponent<player_animation>();
	player->addComponent<HungerComponent>();
	player->addComponent<TirednessComponent>();
	mngr_->setHandler<Player_hdlr>(player);

	//se inicializa la "pantalla" sobre la cual se crean botones de nanogui
	sc_ = new Screen(sdlutils().window(), Vector2i(1920, 1080), "test");
	auto& nwindow = sc_->window("Button demo", Vector2i{ 0, 0 })
		.withLayout<GroupLayout>();
	//funcion lambda usada en el boton
	auto f = [](int a) -> int {a++; return a; };

	//boton basico
	nwindow.label("Push buttons", "sans-bold")._and()
		.button("Plain button", f)
		.withTooltip("This is plain button tips");
	//al colocarlo todo, se utiliza esta funcion para pasarle la info al render
	sc_->performLayout(sdlutils().renderer());
}



void ShelterScene::render()
{
	GameScene::render();
	sc_->drawAll();
}

void ShelterScene::updateScreen(SDL_Event* e)
{
	sc_->onEvent(*e);
}

