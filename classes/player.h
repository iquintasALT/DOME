#pragma once
#include "game_character.h"
#include "../classes/weapon_behaviour.h"
#include "../components/weapon.h"

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
