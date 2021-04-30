#pragma once
#include "game_object.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"
#include "../utils/checkML.h"

class Manager;
class Game;

using CallBackOnClick = void(Manager* g);
class MenuButton : public GameObject {
protected:
	CallBackOnClick* cbOnClick;
	Texture* tex;
	Game* game;

public:
	MenuButton(Vector2D pos, Vector2D size, Texture* t, CallBackOnClick* function, Game* g, Manager* mngr_);
	virtual void update() override;
};