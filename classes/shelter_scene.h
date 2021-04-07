#pragma once
#include "../classes/game_scene.h"
#include "../game/checkML.h"
#include "../classes/crafting_system.h"
#include "../classes/workshop.h"
#include <sdlgui/screen.h>
#include <functional>


class ShelterScene : public GameScene {
private:
	sdlgui::Screen* sc_;
	sdlgui::ListImages craftIcons;
	CraftingSystem* craftSys;
	Workshop* workshop;
	Manager* uselessMngr;

public:
	virtual ~ShelterScene() { delete craftSys, delete uselessMngr; workshop->setActive(false); };
	void init() override;
	virtual void update();
	virtual void render() override;
	void updateScreen(SDL_Event* e);
	void showWidget(sdlgui::Widget& widget, bool cond);
	sdlgui::Widget& createSimpleWidget();
	sdlgui::Widget& createSimpleButton(sdlgui::Vector2i pos, string buttonText, string description, std::function<void()> func);
};