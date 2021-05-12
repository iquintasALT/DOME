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

enum class WeaponType { CLASSIC, LASER, RICOCHET };

class WeaponBehaviour : public GameEntity {
private:
	Weapon* weapon;
	Transform* pl;
	WeaponType weaponType;

	int tierWeapon1 = 1;
	int tierWeapon2 = 1; //Pasar por referencia el level de cada arma
	int tierWeapon3 = 1;

	InventoryController* inv;

	int weaponBullets[3] = { 0, 0, 0 };
	int dispersion = 0;

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
	void upgradeTier();

	void addDispersion(int i);
};