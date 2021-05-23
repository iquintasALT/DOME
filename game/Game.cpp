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
#include "../sdlutils/SoundManager.h"
#include "../sdlutils/SDLUtils.h"
#include "../game/constant_variables.h"
#include "../classes/weapon_behaviour.h"
#include "../classes/camera.h"
#include "../sdlutils/Texture.h"
#include <sstream>

#include "../ecs/Manager.h"
#include "../utils/Vector2D.h"

#include "../classes/menu_scene.h"
#include "../classes/raid_scene.h"
#include "../classes/shelter_scene.h"
#include "../classes/locations_scene.h"
#include "../classes/lose_scene.h"
#include "../classes/pause_scene.h"
#include "../classes/player.h"

#include "../components/hunger_component.h"
#include "../components/tiredness_component.h"
#include "../classes/physiognomy.h"

Game::Game(int totaltime) {
	initLoot();

	states = new GameStateMachine();

	Camera::setMain(new Camera(Vector2D(), 1080, 720));

	framesFPS = 0;
	lastTimeFPS = SDL_GetTicks();
	fpsActive = false;
	fpsText = nullptr;
	shouldRenderFps = false;
}

Game::~Game() {
	delete states;
	delete Camera::mainCamera;
	if (playerCreated) {
		playerSaved->getComponent<InventoryController>()->inventory->forceDelete = true;
		delete playerSaved;
	}
}

void Game::init() {

	SDLUtils::init("DOME", consts::WINDOW_WIDTH, consts::WINDOW_HEIGHT, "./resources/config/resources.json");

	sdlutils().showCursor();
	//sdlutils().toggleFullScreen();

	initLoot();

	states->pushState(new MenuScene(this));
	states->currentState()->init();
	states->currentState()->onLoad();
}

void Game::start() {

	// a boolean to exit the loop
	exit = false;
	SDL_Event event;

	while (!exit) {
		Uint32 startTime = sdlutils().currRealTime();

		soundManager().update();
		while (SDL_PollEvent(&event)) {
			ih().update(event);
		}

		if (event.type == SDL_QUIT) {
			exit = true;
			continue;
		}

		//FPS
		framesFPS++;
		if (lastTimeFPS < SDL_GetTicks() - FPS_INTERVAL * 1000) {
			lastTimeFPS = SDL_GetTicks();
			currentFPS = framesFPS;
			framesFPS = 0;
		}

		sdlutils().clearRenderer();
		states->currentState()->cycle();
		drawFPS(currentFPS);
		sdlutils().presentRenderer();
		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 1000 / consts::FRAME_RATE)
			SDL_Delay((1000 / consts::FRAME_RATE) - frameTime);
	}
}

void Game::drawFPS(int fps) {
	if (fpsActive && shouldRenderFps) {
		std::stringstream ss;
		ss << "FPS: " << fps;
		fpsText = new Texture(sdlutils().renderer(), ss.str(), sdlutils().fonts().at("Orbitron16"), build_sdlcolor(0xffffffff));
		fpsText->render(10, 5);
		delete fpsText;
	}
}

void Game::initLoot() {
	SCENES_LOOT.clear();
	// HOSPITAL, RESTAURANT, RAID, COMMUNICATIONS,NUCLEAR_STATION,SUPERMARKET,SHOP
	// ITEMS n, int cantidad = 0, int w , int h , int x, int y, int row, int col, string desc



	SCENES_LOOT.emplace(SCENES::RAID, vector<vector<I>>{
		{
			I(WATER, 0, 1, 2, 0, 0, 4, 0, "water"),
			I(MEDICAL_COMPONENTS, 5, 2, 2, 1, 0, 3, 2, "componentes medicos para ponerte hasta el culo")
		}
	});

	SCENES_LOOT.emplace(SCENES::SUPERMARKET, vector<vector<I>>{
		{
			I{ SPACESHIP_KEY_ITEMS,0,2,2,0,0,4,2,"spaceship key item" },
			I{ WATER,0,1,2,0,3,4,0,"water" },
			I{ WATER,0,1,2,1,3,4,0,"water" },
			I{ ORGANIC_MATERIAL,0,2,2,2,3,1,2,"organic materials" },
			I{ CLASSIC_AMMO,0,1,1,4,1,2,1,"classic ammo" },
			I{ CLASSIC_AMMO,0,1,1,3,1,2,1,"classic ammo" }, 
			I{ CLASSIC_AMMO,0,1,1,3,2,2,1,"classic ammo" }
		},
		{
			I{ UPGRADE_KIT,0,2,2,0,0,6,2,"upgrade kit" },
			I{ FOOD,0,1,1,2,2,2,0,"food" },
			I{ FOOD,0,1,1,3,1,2,0,"food" },
			I{ ORGANIC_MATERIAL,0,2,2,2,3,1,2,"organic materials" },
			I{ WATER,0,1,2,4,0,4,0,"water" }
		}
	});

	SCENES_LOOT.emplace(SCENES::HOSPITAL, vector<vector<I>>{
		{
			I{ MEDICAL_COMPONENTS,0,1,2,0,0,0,1,"medical components" },
			I{ MEDICAL_COMPONENTS,0,1,2,3,3,0,1,"medical components" },
			I{ MEDICAL_COMPONENTS,0,1,2,4,2,0,1,"medical components" },
			I{ ORGANIC_MATERIAL,0,2,2,2,0,1,2,"organic materials" },
			I{ CLASSIC_AMMO,0,1,1,2,3,2,1,"classic ammo" },
			I{ UPGRADE_KIT,0,2,2,0,3,6,2,"upgrade kit" }
		},
		{
			I{ MEDICAL_COMPONENTS,0,1,2,4,0,0,1,"medical components" },
			I{ANTIDOTE,0,2,2,0,0,1,0,"antidote" },
			I{FOOD,0,1,1,3,0,2,0,"food" },
			I{ SPACESHIP_KEY_ITEMS,0,2,2,3,2,4,2,"spaceship key item" },
			I{ WATER,0,1,2,1,2,4,0,"water" }
		}
	});

	SCENES_LOOT.emplace(SCENES::COMMUNICATIONS, vector<vector<I>>{
		{
			I{ ELECTRONIC_REMAINS,0,1,1,0,1,5,0,"electronic remains" },
			I{ ELECTRONIC_REMAINS,0,1,1,0,2,5,0,"electronic remains" },
			I{ ELECTRONIC_REMAINS,0,1,1,2,4,5,0,"electronic remains" },
			I{ SPACESHIP_KEY_ITEMS,0,2,2,2,0,4,2,"spaceship key item" },
			I{ CLASSIC_AMMO,0,1,1,4,0,2,1,"classic ammo" },
			I{ BUILDING_PARTS,0,2,2,3,2,7,0,"building parts" }
		},
		{
			I{ BUILDING_PARTS,0,2,2,0,1,7,0,"building parts" },
			I{BUILDING_PARTS,0,2,2,3,3,7,0,"building parts" },
			I{UPGRADE_KIT,0,2,2,2,0,6,2,"upgrade kit" },
			I{ MECANICAL_COMPONENTS,0,2,1,0,4,4,1,"mecanical components" },
			I{ CLASSIC_AMMO,0,1,1,2,3,2,1,"classic ammo" }
		}
	});

	SCENES_LOOT.emplace(SCENES::NUCLEAR_STATION, vector<vector<I>>{
		//piso 0
		{
			I{ 0,0, ItemInfo::spaceshipKeyItem() },
			I{ 3,3, ItemInfo::bandage() },
			I{ 3,0, ItemInfo::bandage() },
			I{ 4,0, ItemInfo::water()}
		},
		{
			I{ 0,0, ItemInfo::antidote()},
			I{ 2,0, ItemInfo::medicalComponents() },
			I{ 3,0, ItemInfo::medicalComponents() },
			I{ 3,3, ItemInfo::electronicalRemains()}
		},
		{
			I{ 0,0, ItemInfo::food()},
			I{ 0,1, ItemInfo::food()},
			I{ 0,2, ItemInfo::food()},
			I{ 3,3, ItemInfo::bandage() }
		},
		//piso 1
		{
			I{ 0,3, ItemInfo::bandage() },
			I{ 0,0, ItemInfo::buildingParts() },
			I{ 2,2, ItemInfo::upgradeKit() },
			I{ 3,0, ItemInfo::mechanicalComponents() }

		},
		{
			I{ 0,0, ItemInfo::mechanicalComponents()},
			I{ 0,1, ItemInfo::mechanicalComponents()},
			I{ 1,0, ItemInfo::electronicalRemains()}
		},
		{
			I{ 0,0, ItemInfo::spaceshipKeyItem() },
			I{ 3,3, ItemInfo::electronicalRemains()}

		}
	});

	SCENES_LOOT.emplace(SCENES::SHOP, vector<vector<I>>{
		// ITEMS n, int cantidad = 0, int w , int h , int x, int y, int row, int col, string desc
		//piso -1
		{
			I{ 0,0, ItemInfo::metalPlates() },
			I{ 4,4, ItemInfo::food() },
			I{ 3,3, ItemInfo::medicalComponents() },
		},
		{
			I{ 0,0, ItemInfo::painKiller() },
			I{ 2,2, ItemInfo::painKiller() },
			I{3,3, ItemInfo::laserAmmo()}
		},
		{
			I{ 2,0, ItemInfo::painKiller() },
			I{ 3,3, ItemInfo::bandage() },
			I{0,0, ItemInfo::classicAmmo()}
		},
		// piso 0
		{
			I{ 0,0, ItemInfo::bandage() },
			I{ 1,0, ItemInfo::bandage() },
			I{ 0,1, ItemInfo::spaceshipKeyItem() }
		},
		{
			I{ 0,0, ItemInfo::spaceshipKeyItem() },
			I{ 3,0, ItemInfo::bandage() },
			I{ 0,3, ItemInfo::splint() }, //no saltar
			I{ 4,4, ItemInfo::ricochetAmmo() },
		},
		//piso 1
		{
			I{ 0,0, ItemInfo::antidote()},
			I{ 3,0, ItemInfo::water()},
			I{ 2,0, ItemInfo::food()},
			I{ 3,3, ItemInfo::food()}
		},
		{
			I{ 0,0, ItemInfo::medicalComponents()},
			I{ 0,2, ItemInfo::medicalComponents()},
			I{ 3,0, ItemInfo::water()},
			I{ 4,4, ItemInfo::food()}
		},
		//piso 2
		{
			I{ 0,0, ItemInfo::mechanicalComponents() },
			I{ 1,1, ItemInfo::mechanicalComponents()},
			I{ 2,2, ItemInfo::mechanicalComponents()},
			I{ 3,3, ItemInfo::bandage()},
			I{ 0,3, ItemInfo::mechanicalComponents()}
		},
		{
			I{ 0,0, ItemInfo::upgradeKit() },
			I{ 0,3, ItemInfo::electronicalRemains()},
			I{ 3,3, ItemInfo::electronicalRemains()},
			I{ 4,4, ItemInfo::food()}
		},

		//{metal
		//	I{ 0,0, ItemInfo::antidote()},
		//	I{ 2,0, ItemInfo::painKiller() }, //duran mas los estados
		//	I{ 2,2, ItemInfo::splint() }, //no saltar
		//	I{ 3,0, ItemInfo::bandage() }
		//},
		///*{
		//	I{ ELECTRONIC_REMAINS,0,1,1,0,0,5,0,"electronic remains" },
		//	I{ BUILDING_PARTS,0,2,2,1,1,7,0,"building parts" },
		//	I{ SPACESHIP_KEY_ITEMS,0,2,2,0,3,4,2,"spaceship key item" },
		//	I{ UPGRADE_KIT,0,2,2,3,3,6,2,"upgrade kit" },
		//	I{ FOOD,0,1,1,4,0,2,0,"food" }
		//},*/
		//{
		//	I{ WATER,0,1,2,0,0,4,0,"water" },
		//	I{CLASSIC_AMMO,0,1,1,2,2,2,1,"classic ammo" },
		//	I{ MECANICAL_COMPONENTS,0,2,1,0,4,4,1,"mecanical components" },
		//	I{ ORGANIC_MATERIAL,0,2,2,3,3,1,2,"organic material" }
		//},
		//{
		//	I{ BUILDING_PARTS,0,2,2,0,1,7,0,"building parts" },
		//	I{ BUILDING_PARTS,0,2,2,3,3,7,0,"building parts" },
		//	I{ UPGRADE_KIT,0,2,2,2,0,6,2,"upgrade kit" },
		//	I{ MECANICAL_COMPONENTS,0,2,1,0,4,4,1,"mecanical components" },
		//	I{ CLASSIC_AMMO,0,1,1,2,3,2,1,"classic ammo" }
		//},
		//{
		//	I{ MEDICAL_COMPONENTS,0,1,2,4,0,0,1,"medical components" },
		//	I{ANTIDOTE,0,2,2,0,0,1,0,"antidote" },
		//	I{FOOD,0,1,1,3,0,2,0,"food" },
		//	I{ SPACESHIP_KEY_ITEMS,0,2,2,3,2,4,2,"spaceship key item" },
		//	I{ WATER,0,1,2,1,2,4,0,"water" }
		//},
		//{
		//	I{ WATER,0,1,2,0,3,4,0,"water" }, 
		//	I{ WATER,0,1,2,1,3,4,0,"water" },
		//	I{ ORGANIC_MATERIAL,0,2,2,2,3,1,2,"organic materials" }, 
		//	I{ CLASSIC_AMMO,0,1,1,4,1,2,1,"classic ammo" },
		//	I{ CLASSIC_AMMO,0,1,1,3,1,2,1,"classic ammo" }, 
		//	I{ CLASSIC_AMMO,0,1,1,3,2,2,1,"classic ammo" }
		//},
		//{
		//	I{ UPGRADE_KIT,0,2,2,0,0,6,2,"upgrade kit" },
		//	I{FOOD,0,1,1,2,2,2,0,"food" },  
		//	I{FOOD,0,1,1,3,1,2,0,"food" },
		//	I{ ORGANIC_MATERIAL,0,2,2,2,3,1,2,"organic materials" },
		//	I{ WATER,0,1,2,4,0,4,0,"water" }
		//}
	});
}

void Game::nextDay()
{
	playerSaved->getComponent<HungerComponent>()->decreaseHunger(0.5);
	playerSaved->getComponent<TirednessComponent>()->decreaseTiredness(0.5);
	numDays++;
	if (numDays > consts::MAX_DAYS) playerSaved->getPhysiognomy()->die(WAYSTODIE::DAYS);
}


