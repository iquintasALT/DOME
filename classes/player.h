#pragma once
#include "game_character.h"

class WeaponBehaviour;

class Player :
	public GameCharacter
{
public:
	Player(Manager* mngr_, Point2D pos);
	WeaponBehaviour* getCurrentWeapon();
	WeaponBehaviour* equipWeapon(WeaponBehaviour* newWeapon);

protected:
	WeaponBehaviour* weapon;

};
