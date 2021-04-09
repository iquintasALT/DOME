#pragma once
#include "game_character.h"
#include "../utils/checkML.h"

class RangedEnemy : public GameCharacter
{
public:
	RangedEnemy(Manager* mngr_, Point2D pos);
};

