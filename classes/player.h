#pragma once
#include "game_character.h"
#include "../components/weapon_behaviour.h"
class Player :
	public GameCharacter
{

public:
	Player(Manager* mngr_, Point2D pos);
	WeaponBehaviour* equipWeapon(WeaponBehaviour* newWeapon);
protected:
	Entity* weapon;
};
