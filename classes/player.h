#pragma once
#include "game_character.h"
class Player :
	public GameCharacter
{

public:
	Player(Manager* mngr_, Point2D pos);
};
