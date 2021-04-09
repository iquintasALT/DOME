#include "weapon_behaviour.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Image.h"
#include "../components/Transform.h"

WeaponBehaviour::WeaponBehaviour(float fireRate, float dmg, Manager* mngr, Vector2D playerPos, Transform* playerTr , int typeOfWeapon) : GameEntity(mngr) {
	mngr->addEntity(this);
	addComponent<Transform>(Vector2D(playerPos.getX() + playerTr->getW() / 2, playerPos.getY() + playerTr->getW() * 0.4), 32, 32, 0);
	dmg_ = dmg;

	//Cada arma que tenga un numero del 1 al 3 la primera del 3 al 6 segunda y del 6 al 9 tercera
	if (typeOfWeapon == 1)
	{
		addComponent<Image>(&sdlutils().images().at("weapons"), 3, 3, 0, 0);
	}
	else if(typeOfWeapon == 2)
	{ 
		addComponent<Image>(&sdlutils().images().at("weapons"), 3, 3, 0, 1);
	}
	else if (typeOfWeapon == 3)
	{
		addComponent<Image>(&sdlutils().images().at("weapons"), 3, 3, 0, 2);
	}
	else if (typeOfWeapon == 4)
	{
		addComponent<Image>(&sdlutils().images().at("weapons"), 3, 3, 1, 0);
		weaponMovement = addComponent<ChargeWeapon>(fireRate,1);
	}
	else if (typeOfWeapon == 5)
	{
		addComponent<Image>(&sdlutils().images().at("weapons"), 3, 3, 1, 1);
		weaponMovement = addComponent<ChargeWeapon>(fireRate,2);
	}
	else if (typeOfWeapon == 6)
	{
		addComponent<Image>(&sdlutils().images().at("weapons"), 3, 3, 1, 2);
		weaponMovement = addComponent<ChargeWeapon>(fireRate,3);
	}
	else if (typeOfWeapon == 7)
	{
		addComponent<Image>(&sdlutils().images().at("weapons"), 3, 3, 2, 0);
		weaponMovement = addComponent<RicochetWeapon>(fireRate, playerTr, 2, 1); //Ultimas variables numero de rebotes y tier del arma para explosion
	}
	else if (typeOfWeapon == 8)
	{
		addComponent<Image>(&sdlutils().images().at("weapons"), 3, 3, 2, 1);
		weaponMovement = addComponent<RicochetWeapon>(fireRate, playerTr, 3, 2);
	}
	else if (typeOfWeapon == 9)
	{
		addComponent<Image>(&sdlutils().images().at("weapons"), 3, 3, 2, 2);
		weaponMovement = addComponent<RicochetWeapon>(fireRate, playerTr, 4, 3);
	}
}

Weapon* WeaponBehaviour::getWeaponMovement() {
	return weaponMovement;
}
