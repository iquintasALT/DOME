#pragma once
#include "../classes/game_scene.h"
#include "../game/checkML.h"
#include <sdlgui/screen.h>
#include <functional>


class ShelterScene : public GameScene {
private:
	sdlgui::Screen* sc_;

public:
	void init() override;
	void render() override;
	void updateScreen(SDL_Event* e);
	void showWidget(sdlgui::Widget& widget, bool cond);
	sdlgui::Widget& createSimpleWidget();
	sdlgui::Widget& createSimpleButton(sdlgui::Vector2i pos, string buttonText, string description,
		sdlgui::Widget& ventana);
};