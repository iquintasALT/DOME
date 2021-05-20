#pragma once
#include "game_object.h"
#include "../utils/checkML.h"

class Enemy : public Entity
{
public:
	Enemy(Manager* mngr_, Point2D pos, bool hasGravity);
	void receiveDamage(int damage_);
	int lives = 5;
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