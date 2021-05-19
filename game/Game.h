// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../classes/countdown.h"
#include "../classes/game_scene.h"
#include "../classes/game_state_machine.h"
#include "../utils/checkML.h"
#include <memory>
#include <stack>

// when you are not using the methods of a class, just
// say that it exists, that saves time when parsing files
class Manager;
class Entity;

const enum class SCENES { SHOP, NUCLEAR_STATION, HOSPITAL, COMMUNICATIONS, SUPERMARKET, SHELTER, RAID, SETTINGS, MAINMENU, NONE, CREDITS };
const vector<SCENES> scenes = { SCENES::SHOP,  SCENES::NUCLEAR_STATION,  SCENES::HOSPITAL, SCENES::COMMUNICATIONS,  SCENES::SUPERMARKET };
const vector<int> SCENES_CHESTS = { 0,0,2,1,0 };

const float FPS_INTERVAL = 1.0f;

class Game {
private:
	GameStateMachine* states;

	bool exit;

	int lastTimeFPS; //ultimo registro de fps
	int currentFPS; //el actual numero de fps
	int framesFPS; //frames transcurrido desde el ultimo registro de fps
	bool fpsActive;
	Texture* fpsText;

	void drawFPS(int fps);

public:
	SCENES currentScene;
	map<SCENES, vector<vector<I>>> SCENES_LOOT;
	bool cabin = false, rockets = false, radar = false;

	Game(int totaltime);
	virtual ~Game();
	void init();
	void start();
	inline GameStateMachine* getStateMachine() { return states; }
	void quitGame() { exit = true; }

	void initLoot();
	void setFPSActive(bool value) { fpsActive = value; }
	bool getFPSActive() { return fpsActive; }
	
	// booleano para comprabar si el jugador ha sido creado, para mantener la informaci�n
	// entre escenas. Ponerlo a falso cuando se salga de juego (menu, endScreen, etc.)
	bool playerCreated = false;
	Player* playerSaved = nullptr;

	// contador de dias de juego. Partimos de 0 para dejar claro que no 
	// se ha comenzado la partida, hacer que se haga + 1 para cada transicion a 
	// LocationScene, comparandolo con consts::MAX_DAYS, y haciendo lo necesario cuando se llegue al ultimo dia 
	int numDays = 0;
};