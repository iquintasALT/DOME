#include "../classes/shelter_scene.h"
#include "../components/hunger_component.h"
#include "../components/tiredness_component.h"
#include "../game/Game.h"
#include "locations_scene.h"
#include "../classes/pause_scene.h"
#include "../components/open_station.h"

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

	std::cout << "hey" << std::endl;

	//se inicializa la "pantalla" sobre la cual se crean botones de nanogui
	sc_ = new Screen(sdlutils().window(), Vector2i(sdlutils().width(), sdlutils().height()), "Refugio");
	//se cargan las imagenes de los posibles crafteos
	//craftIcons = loadImageDirectory(sdlutils().renderer(), "./resources/sprites/crafticons");
	//sc_->sdlgui::Screen::initialize(sdlutils().window()); ???

	//ORDEN: 1.CREAR TODOS LOS WIDGETS, 2.ESCONDERLOS, 3.REABRIRLOS CUANDO SE PULSA SU BOTON

	auto& ventana1 = createSimpleWidget(); //se crea ya escondida

	//createSimpleButton(Vector2i(500, 100), "INVENTARIO", "Abre el Inventario", ventana1);
	std::function<void()> openRaidMap = [&]() {g_->getStateMachine()->pushState(new LocationsScene(g_)); };

	sdlgui::Widget& raidMapStation = createSimpleButton(Vector2i(500, 500), "MAP OF DOME 42", "Abre el mapa de la cúpula", openRaidMap);

	//createSimpleButton(Vector2i(500, 300), "DESCANSO", "Permite dormir y recuperar fuerzas", ventana1);

	//createSimpleButton(Vector2i(500, 400), "REPARAR NAVE", "Abre el Inventario", ventana1);

	//createSimpleButton(Vector2i(500, 500), "COMENZAR RAID", "Abre el Inventario", ventana1);

	//al colocarlo todo, se utiliza esta funcion para pasarle la info al render
	sc_->performLayout(sdlutils().renderer());
}



void ShelterScene::update() {
	mngr_->update();

	/*mechanical_Workshop->update();
	medical_Workshop->update();
	sleep_Station->update();*/

	if (ih().keyDownEvent() && ih().isKeyDown(SDL_SCANCODE_ESCAPE)) {
		g_->getStateMachine()->pushState(new PauseScene(g_));
		g_->getStateMachine()->currentState()->init();
	}
}

void ShelterScene::render()
{
	mngr_->render();
	sc_->drawAll();

	/*mechanical_Workshop->render();
	medical_Workshop->render();
	sleep_Station->render();*/
}

void ShelterScene::updateScreen(SDL_Event* e)
{
	sc_->onEvent(*e);
}

void ShelterScene::showWidget(Widget& widget, bool cond)
{
	widget.setEnabled(cond);
	widget.setVisible(cond);
	if (cond) {
		sc_->moveWindowToFront(widget.window());
		widget.setSize(Vector2i(sdlutils().width() * 3 / 4, sdlutils().height() * 3 / 4));
		sc_->centerWindow(widget.window());
	}

}

sdlgui::Widget& ShelterScene::createSimpleWidget()
{
	auto& widget = sc_->window("Crafting", Vector2i{ 0, 0 })
		.withLayout<GroupLayout>();

	////funcion lambda usada en el boton
	auto f = [&]() -> void {
		showWidget(widget, false);
	};

	//boton para cerrar la ventana
	widget
		.button("CERRAR", f)
		.withTooltip("Cierra esta ventana").withLayout<BoxLayout>(Orientation::Horizontal);

	//se esconde la ventana
	showWidget(widget, false);
	return widget;
}


sdlgui::Widget& ShelterScene::createSimpleButton(Vector2i pos, string buttonText, string description,
	std::function<void()> func)
{
	//ventana que contiene al boton
	auto& nwindow = sc_->window(buttonText, pos)
		.withLayout<GroupLayout>();

	//boton para abrir la ventana indicada
	nwindow
		.button("ABRIR", func)
		.withTooltip(description);

	return nwindow;
}



