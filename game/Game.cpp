// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/GravityComponent.h"
#include "../components/KeyboardPlayerCtrl.h"
#include "../components/player_animation.h"
#include "../components/weapon.h"
#include "../ecs/ecs.h"
#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../game/constant_variables.h"
#include "../classes/weapon_behaviour.h"

#include "../ecs/Manager.h"
#include "../utils/Vector2D.h"
#include "box2d.h"

#include "../classes/menu_scene.h"
#include "../classes/raid_scene.h"
#include "../classes/shelter_scene.h"

Game::Game(int totaltime) {
	states = new GameStateMachine();
	timer = new Countdown(totaltime);
}

Game::~Game() {
	delete states;
	delete timer;
}

void Game::init() {

	SDLUtils::init("DOME", 1080, 720, "resources/config/resources.json");
	sdlutils().showCursor();

	states->pushState(new RaidScene());
	//states->pushState(new MenuScene(this));
	states->currentState()->init();
	//states->pushState(new ShelterScene());
	//states->currentState()->init();
	//states->popState();
}

void Game::start() {

	// a boolean to exit the loop
	bool exit = false;
	SDL_Event event;

	while (!exit) {
		Uint32 startTime = sdlutils().currRealTime();

		//ih().clearState();
		while (SDL_PollEvent(&event))
			ih().update(event);

		if (ih().isKeyDown(SDL_SCANCODE_ESCAPE) || event.type == SDL_QUIT) {
			exit = true;
			continue;
		}

		states->currentState()->update();
		states->currentState()->refresh();
		timer->update();
		//mngr_->update();
		//mngr_->refresh();

		sdlutils().clearRenderer();
		//mngr_->render();
		states->currentState()->render();
		timer->render();
		sdlutils().presentRenderer();

		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 1000 / consts::FRAME_RATE)
			SDL_Delay((1000 / consts::FRAME_RATE) - frameTime);
	}

}


