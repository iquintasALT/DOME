#include "game.h"

Game::Game() {
	exit = false;

	//creacion de la ventana de juego
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("TEST", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	//si ha habido algun problema en la creacion de la ventana de SDL, se lanza excepcion
	if (window == nullptr || renderer == nullptr)
		throw string("NO SE HA PODIDO INICIAR SDL");

	b2Vec2 gravity(0.0f, -10.0f);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	TTF_Init();

	loadEntities();
};

Game::~Game() {
	delete renderer;
	delete window;
	for (Entity* e : entities) delete e;
};

void Game::mainLoop() {
	while (!exit) {
		render();
	}
}

void Game::render() {
	SDL_RenderClear(renderer); //Limpia el renderer

	SDL_RenderPresent(renderer);
}

void Game::loadEntities() {
	entities.push_back(new Player());
}