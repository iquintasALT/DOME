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


const enum SCENES { SHELTER, HOSPTITAL, RESTAURANT };

class Game {
private:
	SCENES currentScene;
	map<SCENES, vector<I>> SCENES_LOOT;

	GameStateMachine* states;

	bool exit;
public:
	Game(int totaltime); 
	virtual ~Game();
	void init();
	void start();
	inline GameStateMachine* getStateMachine() { return states; }
	void quitGame() { exit = true; }
	
	void initLoot();
};

