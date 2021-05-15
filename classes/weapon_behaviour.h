#pragma once
//#include "../ecs/Component.h"
//#include "../ecs/Entity.h"
//#include "../components/Transform.h"
//#include "../game/constant_variables.h"
//#include "../ecs/Manager.h"
//#include "../sdlutils/InputHandler.h"
//#include "../components/Image.h"
//#include "../sdlutils/SDLUtils.h"
#include "../classes/game_entity.h"
#include "../game/ecs_defs.h"
//#include "../ecs/Manager.h"
#include "../components/weapon.h"
#include "../utils/checkML.h"
#include "../classes/ricochet_weapon.h"
#include "../classes/charge_weapon.h"
#include <math.h>

enum class WeaponType { CLASSIC, RICOCHET, LASER};

class WeaponAnimation;
class WeaponBehaviour : public GameEntity {
private:
	Weapon* weapon;
	Transform* pl;
	WeaponAnimation* animator_;
	WeaponType weaponType;

	short int weaponTiers [3] ={0, 0, 0};

	InventoryController* inv;

	int weaponBullets[3] = { 0, 0, 0 };
	int bulletSpread = 0;
	inline short int weaponType() { return (short int)weaponType; }; // Quick conversion from enum to array index

public:
	WeaponBehaviour(Manager* mngr, Vector2D playerPos, Transform* playerTr);
	Weapon* getWeapon();

	void setInv(InventoryController* inventory) {
		inv = inventory;
		//weapon->setAmmo();
	}

	void changeWeapon();

	WeaponType typeOfWeapon() { return weaponType; }
	int tierOfWeapon();
	void upgradeCurrentWeapon();

	void addDispersion(int i);
};