#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "SDL_net.h"
#include "SDL_image.h"
#include "box2d.h"

#include "Player.h"

#include <iostream>
#include <list>

using namespace std;

const int WIN_WIDTH = 900;
const int WIN_HEIGHT = 900;

class Game
{
private:
	list<Entity*> entities;

	bool exit;
	SDL_Renderer* renderer;
	SDL_Window* window;

public:
	Game();
	~Game();
	void mainLoop();
	void render();
	void loadEntities();
};

