// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/KeyboardPlayerCtrl.h"
#include "../components/player_animation.h"
#include "../components/weapon.h"
#include "../ecs/ecs.h"
#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../game/constant_variables.h"
#include "../classes/weapon_behaviour.h"
#include "../classes/camera.h"

#include "../ecs/Manager.h"
#include "../utils/Vector2D.h"

#include "../classes/menu_scene.h"
#include "../classes/raid_scene.h"
#include "../classes/shelter_scene.h"
#include "../classes/locations_scene.h"

Game::Game(int totaltime) {
	initLoot();

	states = new GameStateMachine();

	Camera::setMain(new Camera(Vector2D(), consts::WINDOW_WIDTH, consts::WINDOW_HEIGHT));
}

Game::~Game() {
	delete states;
	delete Camera::mainCamera;
}

void Game::init() {

	SDLUtils::init("DOME", consts::WINDOW_WIDTH, consts::WINDOW_HEIGHT, "resources/config/resources.json");
	sdlutils().showCursor();

	initLoot();

	states->pushState(new MenuScene(this));
	states->currentState()->init();
}

void Game::start() {

	// a boolean to exit the loop
	exit = false;
	SDL_Event event;

	while (!exit) {
		Uint32 startTime = sdlutils().currRealTime();

		//ih().clearState();
		while (SDL_PollEvent(&event)) {
			ih().update(event);
		}

		if (event.type == SDL_QUIT) {
			exit = true;
			continue;
		}

		//states->currentState()->update();
		//states->currentState()->refresh();
		//states->currentState()->render();

		sdlutils().clearRenderer();
		states->currentState()->cycle();
		sdlutils().presentRenderer();

		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 1000 / consts::FRAME_RATE)
			SDL_Delay((1000 / consts::FRAME_RATE) - frameTime);
	}

}

void Game::initLoot() {
	SCENES_LOOT.emplace(RAID, vector<vector<I>>{ {I(WATER, 3, 1, 2, 0, 0), I(MEDICAL_COMPONENTS, 5, 2, 2, 1, 0)} });
}


