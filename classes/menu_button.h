#pragma once
#include "game_object.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"

class Game;

using CallBackOnClick = void(Game* g);

class MenuButton : public GameObject {
private:
	CallBackOnClick* cbOnClick;
	Texture* tex;
	Game* game;

public:
	MenuButton(Vector2D pos, Texture* t, CallBackOnClick* function, Game* g, Manager* mngr_);
	void render() const;
	bool handleEvents(const SDL_Event& e);
};