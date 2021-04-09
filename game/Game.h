// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../game/countdown.h"
#include "../classes/game_scene.h"
#include "../classes/game_state_machine.h"
#include "../utils/checkML.h"
#include <memory>
#include <stack>

// when you are not using the methods of a class, just
// say that it exists, that saves time when parsing files
class Manager;

class Game {
private:
	GameStateMachine* states;
	Countdown* timer;

public:
	Game(int totaltime); 
	virtual ~Game();
	void init();
	void start();
	inline GameStateMachine* getStateMachine() { return states; }
};

