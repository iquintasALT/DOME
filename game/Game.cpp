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
#include "../classes/lose_scene.h"

Game::Game(int totaltime) {
	initLoot();

	states = new GameStateMachine();

	Camera::setMain(new Camera(Vector2D(), 1080, 720));
}

Game::~Game() {
	delete states;
	delete Camera::mainCamera;
}

void Game::init() {

	SDLUtils::init("DOME", consts::WINDOW_WIDTH, consts::WINDOW_HEIGHT, "./resources/config/resources.json");
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
	//, HOSPITAL, RESTAURANT, RAID, COMMUNICATIONS,NUCLEAR_STATION,SUPERMARKET,SHOP
// ITEMS n, int cantidad (INUTIL PARA ESTE METODO), int w , int h , int x, int y,int row, int col,string desc
	SCENES_LOOT.emplace(SCENES::RAID, vector<vector<I>>{ {I(WATER, 3, 1, 2, 0, 0, 4, 0, "pues eso, agua. Se bebe"), I(MEDICAL_COMPONENTS, 5, 2, 2, 1, 0, 3, 2, "componentes medicos para ponerte hasta el culo")} });
	SCENES_LOOT.emplace(SCENES::SUPERMARKET, vector<vector<I>>{
		{I{ SPACESHIP_KEY_ITEMS,0,2,2,0,0,4,2,"spaceship key item" }, I{ WATER,0,1,2,0,3,4,0,"water" }, I{ WATER,0,1,2,1,3,4,0,"water" },
			I{ ORGANIC_MATERIAL,0,2,2,2,3,1,2,"organic materials" }, I{ CLASSIC_AMMO,0,1,1,4,1,2,1,"classic ammo" },
			I{ CLASSIC_AMMO,0,1,1,3,1,2,1,"classic ammo" }, I{ CLASSIC_AMMO,0,1,1,3,2,2,1,"classic ammo" }},

		{ I{ UPGRADE_KIT,0,2,2,0,0,6,2,"upgrade kit" }, I{FOOD,0,1,1,2,2,2,0,"food" },  I{FOOD,0,1,1,3,1,2,0,"food" },
			I{ ORGANIC_MATERIAL,0,2,2,2,3,1,2,"organic materials" }, I{ WATER,0,1,2,4,0,4,0,"water" }
		}
	});



	SCENES_LOOT.emplace(SCENES::HOSPITAL, vector<vector<I>>{
		{I{ MEDICAL_COMPONENTS,0,1,2,0,0,0,1,"medical components" }, I{ MEDICAL_COMPONENTS,0,1,2,3,3,0,1,"medical components" }, I{ MEDICAL_COMPONENTS,0,1,2,4,2,0,1,"medical components" },
			I{ ORGANIC_MATERIAL,0,2,2,2,0,1,2,"organic materials" }, I{ CLASSIC_AMMO,0,1,1,2,3,2,1,"classic ammo" },
			I{ UPGRADE_KIT,0,2,2,0,3,6,2,"upgrade kit" }},

		{ I{ MEDICAL_COMPONENTS,0,1,2,4,0,0,1,"medical components" }, I{ANTIDOTE,0,2,2,0,0,1,0,"antidote" },  I{FOOD,0,1,1,3,0,2,0,"food" },
			I{ SPACESHIP_KEY_ITEMS,0,2,2,3,2,4,2,"spaceship key item" }, I{ WATER,0,1,2,1,2,4,0,"water" }
		}
	});


	SCENES_LOOT.emplace(SCENES::COMMUNICATIONS, vector<vector<I>>{
		{I{ ELECTRONIC_REMAINS,0,1,1,0,1,5,0,"electronic remains" }, I{ ELECTRONIC_REMAINS,0,1,1,0,2,5,0,"electronic remains" }, I{ ELECTRONIC_REMAINS,0,1,1,2,4,5,0,"electronic remains" },
			I{ SPACESHIP_KEY_ITEMS,0,2,2,2,0,4,2,"spaceship key item" }, I{ CLASSIC_AMMO,0,1,1,4,0,2,1,"classic ammo" },
			I{ BUILDING_PARTS,0,2,2,3,2,7,0,"building parts" }},

		{ I{ BUILDING_PARTS,0,2,2,0,1,7,0,"building parts" }, I{BUILDING_PARTS,0,2,2,3,3,7,0,"building parts" },  I{UPGRADE_KIT,0,2,2,2,0,6,2,"upgrade kit" },
			I{ MECANICAL_COMPONENTS,0,2,1,0,4,4,1,"mecanical components" }, I{ CLASSIC_AMMO,0,1,1,2,3,2,1,"classic ammo" }
		}
	});

	SCENES_LOOT.emplace(SCENES::NUCLEAR_STATION, vector<vector<I>>{
		{I{ ELECTRONIC_REMAINS,0,1,1,0,0,5,0,"electronic remains" }, I{ BUILDING_PARTS,0,2,2,3,0,7,0,"building parts" }, I{ ELECTRONIC_REMAINS,0,1,1,2,0,5,0,"electronic remains" },
			I{ SPACESHIP_KEY_ITEMS,0,2,2,0,1,4,2,"spaceship key item" }, I{ UPGRADE_KIT,0,2,2,0,3,6,2,"upgrade kit" },
			I{ BUILDING_PARTS,0,2,2,3,3,7,0,"building parts" }},
		
		{ I{ MECANICAL_COMPONENTS,0,2,1,0,2,4,1,"mecanical components" }, I{CLASSIC_AMMO,0,1,1,2,3,2,1,"classic ammo" },  I{UPGRADE_KIT,0,2,2,3,0,6,2,"upgrade kit" },
			I{ MECANICAL_COMPONENTS,0,2,1,0,4,4,1,"mecanical components" }, I{ SPACESHIP_KEY_ITEMS,0,2,2,3,3,4,2,"spaceship key items" }
		}
	});

	SCENES_LOOT.emplace(SCENES::SHOP, vector<vector<I>>{
		{I{ ELECTRONIC_REMAINS,0,1,1,0,0,5,0,"electronic remains" }, I{ BUILDING_PARTS,0,2,2,1,1,7,0,"building parts" },
			I{ SPACESHIP_KEY_ITEMS,0,2,2,0,3,4,2,"spaceship key item" }, I{ UPGRADE_KIT,0,2,2,3,3,6,2,"upgrade kit" },
			I{ FOOD,0,1,1,4,0,2,0,"food" }},

		{ I{ WATER,0,1,2,0,0,4,0,"water" }, I{CLASSIC_AMMO,0,1,1,2,2,2,1,"classic ammo" },
			I{ MECANICAL_COMPONENTS,0,2,1,0,4,4,1,"mecanical components" }, I{ ORGANIC_MATERIAL,0,2,2,3,3,1,2,"organic material" }
		}
	});
}


