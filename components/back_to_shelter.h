#pragma once
#include "interactableElement.h"
#include "../classes/game_state_machine.h"

class Game;

class BackToShelter :
    public InteractableElement
{
private:
	GameStateMachine* states;
	Entity* player;

public: 
	BackToShelter(Game* g);
	void init() override;
	void Interact() override;
	void update() override;
};

