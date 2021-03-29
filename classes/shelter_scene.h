#pragma once
#include "../classes/game_scene.h"
#include "../game/checkML.h"
#include <sdlgui/screen.h>


class ShelterScene : public GameScene {
public:
	void init() override;
	void render() override;
	void updateScreen(SDL_Event* e);
private:
	sdlgui::Screen* sc_;
};