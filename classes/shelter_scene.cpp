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
	auto tr = player->addComponent<Transform>(Vector2D(), 32, 64, 0);
	player->addComponent<Image>(&sdlutils().images().at("player"), 3, 14, 0, 0);
	player->addComponent<ParticleSystem>(&sdlutils().images().at("dust"), 1, 1, 0, 0);
	player->addComponent<RigidBody>();
	player->addComponent<KeyboardPlayerCtrl>();
	player->addComponent<player_animation>();
	player->addComponent<HungerComponent>();
	player->addComponent<TirednessComponent>();
	mngr_->setHandler<Player_hdlr>(player);

	craftSys = new CraftingSystem(mngr_);

	uselessMngr = new Manager();
	mechanical_Workshop = new Workshop(uselessMngr, craftSys);
	mechanical_Workshop->setWorkshopItems(vector<ITEMS>{METAL_PLATES, WEAPON_UPGRADE, CLASSIC_AMMO, BACKPACK_UPGRADE, ARMOUR_UPGRADE });

	medical_Workshop = new Workshop(uselessMngr, craftSys);
	medical_Workshop->setWorkshopItems(vector<ITEMS>{ANTIDOTE, BANDAGE, SPLINT});

	//se inicializa la "pantalla" sobre la cual se crean botones de nanogui
	sc_ = new Screen(sdlutils().window(), Vector2i(sdlutils().width(), sdlutils().height()), "Refugio");
	//se cargan las imagenes de los posibles crafteos
	//craftIcons = loadImageDirectory(sdlutils().renderer(), "./resources/sprites/crafticons");
	//sc_->sdlgui::Screen::initialize(sdlutils().window()); ???

	//ORDEN: 1.CREAR TODOS LOS WIDGETS, 2.ESCONDERLOS, 3.REABRIRLOS CUANDO SE PULSA SU BOTON

	auto& ventana1 = createSimpleWidget(); //se crea ya escondida

	//createSimpleButton(Vector2i(500, 100), "INVENTARIO", "Abre el Inventario", ventana1);
	std::function<void()> openMechanicalWorkshop = [&]() { mechanical_Workshop->setRenderFlag(true); };
	std::function<void()> openMedicalWorkshop = [&]() { medical_Workshop->setRenderFlag(true); };

	sdlgui::Widget& windowMechWorkshop = createSimpleButton(Vector2i(500, 200), "MECHANICAL WORKSHOP", "Abre la lista de posibles crafteos", openMechanicalWorkshop);
	sdlgui::Widget& windowMedWorkshop = createSimpleButton(Vector2i(500, 500), "MEDICAL WORKSHOP", "Abre la lista de posibles crafteos", openMedicalWorkshop);

	//createSimpleButton(Vector2i(500, 300), "DESCANSO", "Permite dormir y recuperar fuerzas", ventana1);

	//createSimpleButton(Vector2i(500, 400), "REPARAR NAVE", "Abre el Inventario", ventana1);

	//createSimpleButton(Vector2i(500, 500), "COMENZAR RAID", "Abre el Inventario", ventana1);

	//al colocarlo todo, se utiliza esta funcion para pasarle la info al render
	sc_->performLayout(sdlutils().renderer());
}



void ShelterScene::update() {
	mngr_->update();

	mechanical_Workshop->update();
	medical_Workshop->update();
}

void ShelterScene::render()
{
	mngr_->render();
	sc_->drawAll();

	mechanical_Workshop->render();
	medical_Workshop->render();
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



