#pragma once
#include "game_object.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"
#include "../utils/checkML.h"

class Game;

using CallBackOnClick = void(Game* g);

class MenuButton : public GameObject {
protected:
	CallBackOnClick* cbOnClick;
	Texture* tex;
	Game* game;

public:
	MenuButton(Vector2D pos, Texture* t, CallBackOnClick* function, Game* g, Manager* mngr_);
	void update() override;
};