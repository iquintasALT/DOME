// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../classes/countdown.h"
#include "../classes/game_scene.h"
#include "../classes/game_state_machine.h"
#include "../utils/checkML.h"
#include <memory>
#include <stack>
#include "../classes/player_save_data.h"
// when you are not using the methods of a class, just
// say that it exists, that saves time when parsing files
class Manager;
class Entity;

const enum class SCENES { NUCLEAR_STATION, SUPERMARKET, COMMUNICATIONS, HOSPITAL, SHOP, SHELTER, SETTINGS, MAINMENU, CREDITS, TUTORIAL, NONE };

const float FPS_INTERVAL = 1.0f;

class Game {
private:
	GameStateMachine* states;

	bool exit;

	int gameID; 

	int lastTimeFPS; //ultimo registro de fps
	int currentFPS;  //el actual numero de fps
	int framesFPS;   //frames transcurrido desde el ultimo registro de fps
	bool fpsActive; bool shouldRenderFps;
	Texture* fpsText;

	void drawFPS(int fps);
	void clearSceneLoot();

public:
	SCENES currentScene;
	map<SCENES, vector<vector<pair<ItemInfo*, Vector2D>>>> SCENES_LOOT;
	bool cabin = false, rockets = false, radar = false;

	Game(int totaltime);
	virtual ~Game();
	void init();
	void start();
	inline GameStateMachine* getStateMachine() { return states; }
	void quitGame() { exit = true; }

	void initLoot();

	int getGameID() { return gameID; }
	void increaseGameID() { gameID++; }

	void setFPSActive(bool value) { fpsActive = value; }
	bool getFPSActive() { return fpsActive; }
	void setShouldRenderFPS(bool value) { shouldRenderFps = value; }
	
	// datos guardados del jugador para poder trasladarlos entre escenas
	PlayerSaveData* playerSavedData;

	// booleano que control si hay fullscreen activo
	bool fullscreen = false;

	// cursor customizado
	Point2D cursorCenter;
	Texture* cursor;
	void renderCursor();

	// contador de dias de juego. Partimos de 0 para dejar claro que no 
	// se ha comenzado la partida, hacer que se haga + 1 para cada transicion a 
	// LocationScene, comparandolo con consts::MAX_DAYS, y haciendo lo necesario cuando se llegue al ultimo dia 
	int numDays = 0;
};

