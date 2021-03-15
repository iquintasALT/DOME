#pragma once
#include "game_character.h"

class Enemy :
    public GameCharacter
{
public:
    static Entity* newEnemy(Manager* mngr_, Point2D pos);
};

