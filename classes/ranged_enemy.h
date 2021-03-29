#pragma once
#include "game_character.h"
#include "../game/checkML.h"

class RangedEnemy : public GameCharacter
{
public:
	RangedEnemy(Manager* mngr_, Point2D pos);
};

