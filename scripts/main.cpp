#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "SDL_net.h"
#include "SDL_image.h"
#include "box2d.h"

#include <iostream>

using namespace std;

int main(int a, char* argv[])
{
	//creacion de la ventana de juego
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("TEST", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		900, 900, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	//si ha habido algun problema en la creacion de la ventana de SDL, se lanza excepcion
	if (window == nullptr || renderer == nullptr)
		throw string("NO SE HA PODIDO INICIAR SDL");

	b2Vec2 gravity(0.0f, -10.0f);

	TTF_Init();

	SDL_Delay(5000);
	return 0;
}