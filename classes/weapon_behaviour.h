#pragma once
#include "../utils/checkML.h"
#include "../ecs/Entity.h"
#include "../utils/Vector2D.h"
#include "../components/weapon.h"
#include "../classes/ricochet_weapon.h"
#include "../classes/charge_weapon.h"
#include <math.h>

class WeaponAnimation;
class WeaponBehaviour : public Entity {
private:
	Weapon* weapon;
	Transform* pl;
	WeaponAnimation* animator_;

	Weapon::WeaponType weaponType;
	short int weaponTiers [3] = {0, 0, 0};

	InventoryController* inv_;

	int bulletSpread = 0;

public:
	WeaponBehaviour(Manager* mngr, Vector2D playerPos, Transform* playerTr);
	~WeaponBehaviour();
	Weapon* getCurrentWeapon();

	void setInv(InventoryController* inventory) { inv_ = inventory; }
	InventoryController* getInv() { return inv_; };

	void changeWeapon();

	Weapon::WeaponType typeOfWeapon() { return weaponType; }
	short int * tiersOfWeapons() { return weaponTiers; }
	void updateWeapons(short int* newTiers);
	int tierOfWeapon();
	void upgradeCurrentWeapon();

	void addDispersion(int i);

};