#pragma once
#include "game_character.h"
#include "../game/checkML.h"
class Physiognomy;
class WeaponBehaviour;

class Player : public GameCharacter
{
protected:
	WeaponBehaviour* weapon;
	Physiognomy* physiognomy;

public:
	Player(Manager* mngr_, Point2D pos);
	~Player();
	WeaponBehaviour* getCurrentWeapon();
	WeaponBehaviour* equipWeapon(WeaponBehaviour* newWeapon);
	Physiognomy* getPhysiognomy();
};
