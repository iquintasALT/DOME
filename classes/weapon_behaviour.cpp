#include "weapon_behaviour.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Image.h"
#include "../components/Transform.h"
#include "../game/constant_variables.h"

WeaponBehaviour::WeaponBehaviour(Manager* mngr, Vector2D playerPos, Transform* playerTr) : GameEntity(mngr), pl(playerTr), weaponMovement(nullptr) {
	mngr->addEntity(this);
	mngr->addRenderLayer<Bullets>(this);

	addComponent<Transform>(Vector2D(playerPos.getX() + playerTr->getW() / 2, playerPos.getY() + playerTr->getW() * 0.4), 38, 24, 0);

	addComponent<Image>(&sdlutils().images().at("weapons_arms"), 3, 3, 0, 0);
	weaponMovement = addComponent<Weapon>(consts::WEAPON_TIER1_FIRERATE, consts::WEAPON_TIER1_DAMAGE, 20);
	weaponType = WeaponType::CLASSIC;
}

Weapon* WeaponBehaviour::getWeaponMovement() {
	return weaponMovement;
}

void WeaponBehaviour::changeWeapon()
{
	this->removeComponent<Image>();

	if (weaponType == WeaponType::CLASSIC)
	{
		this->removeComponent<Weapon>();
		Component* img = addComponent<Image>(&sdlutils().images().at("weapons_arms"), 3, 3, 1, 0);
		weaponMovement = addComponent<ChargeWeapon>(consts::CHARGE_TIER1_FIRERATE, consts::CHARGE_TIER1_DAMAGE);
		if (tierWeapon2 != 1) weaponMovement->upgradeTier(tierWeapon2);
		weaponType = WeaponType::LASER;
	}
	else if (weaponType == WeaponType::LASER)
	{
		this->removeComponent<ChargeWeapon>();
		Component* img = addComponent<Image>(&sdlutils().images().at("weapons_arms"), 3, 3, 2, 0);
		weaponMovement = addComponent<RicochetWeapon>(consts::RICOCHET_TIER1_FIRERATE, consts::RICOCHET_TIER1_DAMAGE, pl, 3, 1);
		if (tierWeapon3 != 1) weaponMovement->upgradeTier(tierWeapon3);
		weaponType = WeaponType::RICOCHET;
	}
	else
	{
		this->removeComponent<RicochetWeapon>();
		Component* img = addComponent<Image>(&sdlutils().images().at("weapons_arms"), 3, 3, 0, 0);
		weaponMovement = addComponent<Weapon>(consts::WEAPON_TIER1_FIRERATE, consts::WEAPON_TIER1_DAMAGE);
		if (tierWeapon1 != 1) weaponMovement->upgradeTier(tierWeapon1);
		weaponType = WeaponType::CLASSIC;
	}
}

int WeaponBehaviour::tierOfWeapon()
{
	if (weaponType == WeaponType::CLASSIC)
	{
		return tierWeapon1;
	}
	if (weaponType == WeaponType::LASER)
	{
		return tierWeapon2;
	}
	else
	{
		return tierWeapon3;
	}
}

void WeaponBehaviour::upgradeTier() {
	if (weaponType == WeaponType::CLASSIC) {
		tierWeapon1++;
		weaponMovement->upgradeTier(tierWeapon1);
	}
	if (weaponType == WeaponType::LASER) {
		tierWeapon2++;
		weaponMovement->upgradeTier(tierWeapon2);
	}
	else {
		tierWeapon3++;
		weaponMovement->upgradeTier(tierWeapon3);
	}
}