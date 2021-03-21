#pragma once
#include "game_character.h"
#include "../game/checkML.h"
class Physiognomy;
class WeaponBehaviour;

class Player :
	public GameCharacter
{
public:
	Player(Manager* mngr_, Point2D pos);
	WeaponBehaviour* getCurrentWeapon();
	WeaponBehaviour* equipWeapon(WeaponBehaviour* newWeapon);
	Physiognomy* getPhysiognomy();

protected:
	WeaponBehaviour* weapon;
	Physiognomy* physiognomy;
};
