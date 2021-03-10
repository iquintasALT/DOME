// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/GravityComponent.h"
#include "../components/KeyboardPlayerCtrl.h"
#include "../ecs/ecs.h"
#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

#include "../ecs/Manager.h"
#include "../utils/Vector2D.h"
#include "box2d.h"

Game::Game(int totaltime) {
	mngr_.reset(new Manager());
	lefttime = totaltime; //Recibe los miliseegundos de tiempo en raid
	starttime = SDL_GetTicks();
	updatetime = SDL_GetTicks();
}

Game::~Game() {
}

void Game::init() {

	SDLUtils::init("DOME", 1080, 720, "resources/config/resources.json");

	Entity* player = mngr_->addEntity();
	player->addComponent<Transform>(Vector2D(), Vector2D(), 32, 64, 0);
	player->addComponent<Image>(&sdlutils().images().at("player"), 3, 6, 0, 0);
	player->addComponent<GravityComponent>();
	player->addComponent<KeyboardPlayerCtrl>();
}

void Game::start() {

	// a boolean to exit the loop
	bool exit = false;
	SDL_Event event;

	while (!exit && lefttime > 0) {
		Uint32 startTime = sdlutils().currRealTime();

		ih().clearState();
		while (SDL_PollEvent(&event))
			ih().update(event);

		if (ih().isKeyDown(SDL_SCANCODE_ESCAPE)) {
			exit = true;
			continue;
		}

		timerupdate();

		mngr_->update();
		mngr_->refresh();

		sdlutils().clearRenderer();
		mngr_->render();
		sdlutils().presentRenderer();

		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 1000 / 60)
			SDL_Delay((1000 / 60) - frameTime);
	}

}

void Game::timerupdate()
{
	
	lefttime -= SDL_GetTicks() - starttime; //Restamos el tiempoque ha pasado
	starttime = SDL_GetTicks();
	
	if (lefttime <= 0)
	{
		std::cout << "Carlos Leon llamalo Angel";
	}
	else if(updatetime + 1000 <= SDL_GetTicks())
	{
		updatetime = SDL_GetTicks();
		int seg = lefttime / 1000;
		int min = seg/60;
		seg = seg % 60;
		if (min < 10)
		{
			std::cout << "0" << min;
		}
		else
		{
			std::cout <<  min;
		}
		std::cout << ":";
		if (seg < 10)
		{
			std::cout << "0" << seg << std::endl;
		}
		else
		{
			std::cout << seg << std::endl;
		}
		
		
	}
}

