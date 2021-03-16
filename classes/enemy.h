#pragma once
#include "game_character.h"

class Enemy :
    public GameCharacter
{
public:
    Enemy(Manager* mngr_, Point2D pos);
};

