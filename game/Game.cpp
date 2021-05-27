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
#include "../sdlutils/InputHandler.h"

using namespace std;

Game::Game(int totaltime) {
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
		delete playerSaved;
	}

	clearSceneLoot();
	std::cout << "Gracias por jugar";

	delete playerSavedData;
}


void Game::init() {
	playerSavedData = new PlayerSaveData();

	SDLUtils::init("DOME", consts::WINDOW_WIDTH, consts::WINDOW_HEIGHT, "./resources/config/resources.json");
	sdlutils().hideCursor();

	//sdlutils().toggleFullScreen();

	//initLoot();
	
	cursor = &sdlutils().images().at("cursor");
	cursorCenter = Vector2D(0.5, 0.5);

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
		renderCursor();
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

	//SCENES_LOOT.clear();
	//, HOSPITAL, RESTAURANT, RAID, COMMUNICATIONS,NUCLEAR_STATION,SUPERMARKET,SHOP
	// ITEMS n, int cantidad (INUTIL PARA ESTE METODO), int w , int h , int x, int y,int row, int col,string desc

	clearSceneLoot();

	SCENES_LOOT.emplace(SCENES::RAID, vector<vector<pair<ItemInfo*, Vector2D>>> {
		{
			make_pair(CraftingSystem::getItemInfo(WATER), Vector2D(0, 0)), make_pair(CraftingSystem::getItemInfo(MEDICAL_COMPONENTS), Vector2D(1, 0))
		}
	});

	SCENES_LOOT.emplace(SCENES::SHELTER, vector<vector<pair<ItemInfo*, Vector2D>>> {
		//to store items on shelter
		{
		
		}
	});

	SCENES_LOOT.emplace(SCENES::NUCLEAR_STATION, vector<vector<pair<ItemInfo*, Vector2D>>> { //SUPERMARKET
		{
			make_pair(CraftingSystem::getItemInfo(SPACESHIP_KEY_ITEMS), Vector2D(0, 0)), make_pair(CraftingSystem::getItemInfo(WATER), Vector2D(0, 3)),
				make_pair(CraftingSystem::getItemInfo(WATER), Vector2D(1, 3)), make_pair(CraftingSystem::getItemInfo(ORGANIC_MATERIAL), Vector2D(2, 3)),
				make_pair(CraftingSystem::getItemInfo(LASER_AMMO), Vector2D(4, 4)), make_pair(CraftingSystem::getItemInfo(RICOCHET_AMMO), Vector2D(2, 2)),
				make_pair(CraftingSystem::getItemInfo(CLASSIC_AMMO), Vector2D(3, 2)), make_pair(CraftingSystem::getItemInfo(METAL_PLATES), Vector2D(2, 0)),
				make_pair(CraftingSystem::getItemInfo(BANDAGE), Vector2D(4, 0))
		},
		{ make_pair(CraftingSystem::getItemInfo(UPGRADE_KIT), Vector2D(0, 0)), make_pair(CraftingSystem::getItemInfo(FOOD), Vector2D(2, 2)),
				make_pair(CraftingSystem::getItemInfo(FOOD), Vector2D(3, 1)),
				make_pair(CraftingSystem::getItemInfo(ORGANIC_MATERIAL), Vector2D(2, 3)), make_pair(CraftingSystem::getItemInfo(LASER_AMMO), Vector2D(4, 0)),
				make_pair(CraftingSystem::getItemInfo(BUILDING_PARTS), Vector2D(0, 2)), make_pair(CraftingSystem::getItemInfo(BANDAGE), Vector2D(4, 4)),
				make_pair(CraftingSystem::getItemInfo(BANDAGE), Vector2D(4, 2))
		}
	});

	SCENES_LOOT.emplace(SCENES::HOSPITAL, vector<vector<pair<ItemInfo*, Vector2D>>> { //COMUNICATIONS
		{   make_pair(CraftingSystem::getItemInfo(UPGRADE_KIT), Vector2D(3, 3)),
			make_pair(CraftingSystem::getItemInfo(MEDICAL_COMPONENTS), Vector2D(4, 1)), make_pair(CraftingSystem::getItemInfo(ORGANIC_MATERIAL), Vector2D(2, 0)),
			make_pair(CraftingSystem::getItemInfo(CLASSIC_AMMO), Vector2D(2, 3)), make_pair(CraftingSystem::getItemInfo(UPGRADE_KIT), Vector2D(0, 3)),
			make_pair(CraftingSystem::getItemInfo(BANDAGE), Vector2D(1, 2)), make_pair(CraftingSystem::getItemInfo(BANDAGE), Vector2D(3, 2))
		},
		{ make_pair(CraftingSystem::getItemInfo(MEDICAL_COMPONENTS), Vector2D(4, 0)), make_pair(CraftingSystem::getItemInfo(ANTIDOTE), Vector2D(0, 0)),
				make_pair(CraftingSystem::getItemInfo(RICOCHET_AMMO), Vector2D(3, 0)),
				make_pair(CraftingSystem::getItemInfo(SPACESHIP_KEY_ITEMS), Vector2D(3, 2)), make_pair(CraftingSystem::getItemInfo(WATER), Vector2D(1, 2)),
				make_pair(CraftingSystem::getItemInfo(BANDAGE), Vector2D(0, 4)),
				make_pair(CraftingSystem::getItemInfo(BANDAGE), Vector2D(2, 3))
		},
		{ make_pair(CraftingSystem::getItemInfo(LASER_AMMO), Vector2D(3, 3)),
		make_pair(CraftingSystem::getItemInfo(MEDICAL_COMPONENTS), Vector2D(0, 0)), make_pair(CraftingSystem::getItemInfo(ORGANIC_MATERIAL), Vector2D(2, 0)),
		make_pair(CraftingSystem::getItemInfo(CLASSIC_AMMO), Vector2D(2, 3)), make_pair(CraftingSystem::getItemInfo(WATER), Vector2D(0, 3)),
		make_pair(CraftingSystem::getItemInfo(BANDAGE), Vector2D(1, 2)), make_pair(CraftingSystem::getItemInfo(RICOCHET_AMMO), Vector2D(3, 2))
		}
	});


	SCENES_LOOT.emplace(SCENES::COMMUNICATIONS, vector<vector<pair<ItemInfo*, Vector2D>>> { //HOSPITAL
		{make_pair(CraftingSystem::getItemInfo(BANDAGE), Vector2D(0, 1)), make_pair(CraftingSystem::getItemInfo(WATER), Vector2D(0, 2)),
			make_pair(CraftingSystem::getItemInfo(ELECTRONIC_REMAINS), Vector2D(2, 4)), make_pair(CraftingSystem::getItemInfo(FOOD), Vector2D(2, 0)),
			make_pair(CraftingSystem::getItemInfo(CLASSIC_AMMO), Vector2D(4, 0)), make_pair(CraftingSystem::getItemInfo(BUILDING_PARTS), Vector2D(3, 2)),
			make_pair(CraftingSystem::getItemInfo(RICOCHET_AMMO), Vector2D(0, 4))
		},
		{ make_pair(CraftingSystem::getItemInfo(BUILDING_PARTS), Vector2D(3, 3)),
				make_pair(CraftingSystem::getItemInfo(UPGRADE_KIT), Vector2D(2, 0)), make_pair(CraftingSystem::getItemInfo(BANDAGE), Vector2D(4, 0)), 
				make_pair(CraftingSystem::getItemInfo(BANDAGE), Vector2D(1, 3)), make_pair(CraftingSystem::getItemInfo(BANDAGE), Vector2D(4, 2)),
				make_pair(CraftingSystem::getItemInfo(MECANICAL_COMPONENTS), Vector2D(0, 4)), make_pair(CraftingSystem::getItemInfo(MEDICAL_COMPONENTS), Vector2D(2, 3))
		},
		{ make_pair(CraftingSystem::getItemInfo(ORGANIC_MATERIAL), Vector2D(1, 0)), make_pair(CraftingSystem::getItemInfo(RICOCHET_AMMO), Vector2D(3, 3)),
			make_pair(CraftingSystem::getItemInfo(LASER_AMMO), Vector2D(4, 0)), make_pair(CraftingSystem::getItemInfo(BANDAGE), Vector2D(4, 3)),
			make_pair(CraftingSystem::getItemInfo(BANDAGE), Vector2D(1, 4))
		}
	});

	SCENES_LOOT.emplace(SCENES::SHOP, vector<vector<pair<ItemInfo*, Vector2D>>> {  //NUCLEAR
		{make_pair(CraftingSystem::getItemInfo(ELECTRONIC_REMAINS), Vector2D(0, 0)), make_pair(CraftingSystem::getItemInfo(BUILDING_PARTS), Vector2D(3, 0)),
			make_pair(CraftingSystem::getItemInfo(ELECTRONIC_REMAINS), Vector2D(2, 0)), make_pair(CraftingSystem::getItemInfo(SPACESHIP_KEY_ITEMS), Vector2D(0, 1)),
			make_pair(CraftingSystem::getItemInfo(UPGRADE_KIT), Vector2D(0, 3)), make_pair(CraftingSystem::getItemInfo(SPLINT), Vector2D(3, 3)),
			make_pair(CraftingSystem::getItemInfo(BANDAGE), Vector2D(2, 2)), make_pair(CraftingSystem::getItemInfo(RICOCHET_AMMO), Vector2D(2, 4))
		},
		{ make_pair(CraftingSystem::getItemInfo(MECANICAL_COMPONENTS), Vector2D(0, 3)), make_pair(CraftingSystem::getItemInfo(CLASSIC_AMMO), Vector2D(0, 0)),
				make_pair(CraftingSystem::getItemInfo(WATER), Vector2D(3, 0)),
				make_pair(CraftingSystem::getItemInfo(MECANICAL_COMPONENTS), Vector2D(0, 4)), make_pair(CraftingSystem::getItemInfo(SPACESHIP_KEY_ITEMS), Vector2D(3, 3)),
				make_pair(CraftingSystem::getItemInfo(RICOCHET_AMMO), Vector2D(3, 2)), make_pair(CraftingSystem::getItemInfo(METAL_PLATES), Vector2D(0, 1)),
				make_pair(CraftingSystem::getItemInfo(BANDAGE), Vector2D(4, 0)),
		}
	});

	SCENES_LOOT.emplace(SCENES::SUPERMARKET, vector<vector<pair<ItemInfo*, Vector2D>>> { //SHOP
		{make_pair(CraftingSystem::getItemInfo(ELECTRONIC_REMAINS), Vector2D(0, 0)), make_pair(CraftingSystem::getItemInfo(BUILDING_PARTS), Vector2D(1, 1)),
			make_pair(CraftingSystem::getItemInfo(SPACESHIP_KEY_ITEMS), Vector2D(0, 3)),
			make_pair(CraftingSystem::getItemInfo(UPGRADE_KIT), Vector2D(3, 3)), make_pair(CraftingSystem::getItemInfo(FOOD), Vector2D(4, 0)),
			make_pair(CraftingSystem::getItemInfo(BANDAGE), Vector2D(4, 1)), make_pair(CraftingSystem::getItemInfo(BANDAGE), Vector2D(0, 2)),
		},
		{ make_pair(CraftingSystem::getItemInfo(WATER), Vector2D(0, 0)), make_pair(CraftingSystem::getItemInfo(CLASSIC_AMMO), Vector2D(2, 2)),
				make_pair(CraftingSystem::getItemInfo(MECANICAL_COMPONENTS), Vector2D(0, 4)), make_pair(CraftingSystem::getItemInfo(ORGANIC_MATERIAL), Vector2D(3, 3)),
			 make_pair(CraftingSystem::getItemInfo(CLASSIC_AMMO), Vector2D(4, 2)),  make_pair(CraftingSystem::getItemInfo(ORGANIC_MATERIAL), Vector2D(3, 0)),
			make_pair(CraftingSystem::getItemInfo(BANDAGE), Vector2D(0, 3)), make_pair(CraftingSystem::getItemInfo(BANDAGE), Vector2D(1, 0))
		}
	});
}

void Game::clearSceneLoot()
{
	//el pair es iteminfo/posicion en el inventario del loot
	int i = 1;
	for (auto a : SCENES_LOOT) { //Esto es para eliminar el loot anterior y dejarlo vacio para uno nuevo
		for (auto b : a.second) {
			for (auto& c : b) {
				auto d = c.first;
				std::cout << "eliminado itemInfo " << i++ << std::endl;
				delete d;
			}
			b.clear();
		}
		a.second.clear();
	}
	SCENES_LOOT.clear();
}

void Game::nextDay()
{
	numDays++;
	if (numDays > consts::MAX_DAYS) playerSaved->getPhysiognomy()->die(WAYSTODIE::DAYS);
}


void Game::renderCursor() {
	auto mousePos = ih().getMousePos();
	int w = cursor->width();
	int h = cursor->height();

	int x = mousePos.first - cursorCenter.getX() * w;
	int y = mousePos.second - cursorCenter.getY() * h;
	SDL_Rect dest{
		x, y, w, h
	};
	cursor->render(dest);
}
