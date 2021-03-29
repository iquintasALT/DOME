#pragma once
#include "game_character.h"
#include "../game/checkML.h"

class Enemy : public GameCharacter
{
public:
	Enemy(Manager* mngr_, Point2D pos);
};

class DefaultEnemy : public Enemy
{
public:
	DefaultEnemy(Manager* mngr_, Point2D pos);
};

class FlyingEnemy : public Enemy
{
public:
	FlyingEnemy(Manager* mngr_, Point2D pos);
};
