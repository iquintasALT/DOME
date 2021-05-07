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

const enum class SCENES {  SHELTER, HOSPITAL, RESTAURANT, RAID, SETTINGS, MAINMENU, NONE, CREDITS};
const vector<int> SCENES_CHESTS = { 0,0,2,1,0 };

class Game {
private:
	GameStateMachine* states;

	bool exit;
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
	//Entity* player;
	bool playerCreated = false;
};