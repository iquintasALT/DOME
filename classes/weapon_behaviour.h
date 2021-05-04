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

class WeaponBehaviour : public GameEntity {
private:
	Weapon* weaponMovement;
	Transform* pl;
	int type;
	int type1 = 2;
	int type2 = 2; //Pasar por referencia el level de cada arma
	int type3 = 2;
public:
	WeaponBehaviour(Manager* mngr, Vector2D playerPos, Transform* playerTr, int typeOfWeapon);
	Weapon* getWeaponMovement();

	void changeWeapon();

	int typeOfWeapon() { return type; }
	int tierOfWeapon();
};