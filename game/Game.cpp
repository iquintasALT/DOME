// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/GravityComponent.h"
#include "../components/KeyboardPlayerCtrl.h"
#include "../components/player_animation.h"
#include "../ecs/ecs.h"
#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../game/constant_variables.h"

#include "../ecs/Manager.h"
#include "../utils/Vector2D.h"
#include "box2d.h"

Game::Game(int totaltime) {
	mngr_.reset(new Manager());
	timer = new Countdown(totaltime);
}

Game::~Game() {
}

void Game::init() {

	SDLUtils::init("DOME", 1080, 720, "resources/config/resources.json");

	Entity* player = mngr_->addEntity();
	player->addComponent<Transform>(Vector2D(), Vector2D(), 32, 64, 0);
	player->addComponent<Image>(&sdlutils().images().at("player"), 2, 14, 0, 0);
	player->addComponent<player_animation>();
	player->addComponent<GravityComponent>();
	player->addComponent<KeyboardPlayerCtrl>();
}

void Game::start() {

	// a boolean to exit the loop
	bool exit = false;
	SDL_Event event;

	while (!exit ) {
		Uint32 startTime = sdlutils().currRealTime();

		ih().clearState();
		while (SDL_PollEvent(&event))
			ih().update(event);

		if (ih().isKeyDown(SDL_SCANCODE_ESCAPE)) {
			exit = true;
			continue;
		}

		timer->update();
		mngr_->update();
		mngr_->refresh();

		sdlutils().clearRenderer();
		mngr_->render();
		sdlutils().presentRenderer();

		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 1000 / consts::FRAME_RATE)
			SDL_Delay((1000 / consts::FRAME_RATE) - frameTime);
	}

}


