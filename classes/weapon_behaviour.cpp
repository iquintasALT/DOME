#include "weapon_behaviour.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Image.h"
#include "../components/Transform.h"
#include "../game/constant_variables.h"

WeaponBehaviour::WeaponBehaviour(Manager* mngr, Vector2D playerPos, Transform* playerTr) : GameEntity(mngr), pl(playerTr), weapon(nullptr) {
	mngr->addEntity(this);
	mngr->addRenderLayer<Bullets>(this);

	addComponent<Transform>(Vector2D(playerPos.getX() + playerTr->getW() / 2, playerPos.getY() + playerTr->getW() * 0.4), 38, 24, 0);

	addComponent<Image>(&sdlutils().images().at("weapons_arms"), 3, 3, 0, 0);
	weapon = addComponent<Weapon>(consts::WEAPON_TIER1_FIRERATE, consts::WEAPON_TIER1_DAMAGE, 20);
	weaponType = WeaponType::CLASSIC;
}

Weapon* WeaponBehaviour::getWeapon() {
	return weapon;
}

void WeaponBehaviour::changeWeapon()
{
	this->removeComponent<Image>();

	if (weaponType == WeaponType::CLASSIC)
	{
		this->removeComponent<Weapon>();
		Component* img = addComponent<Image>(&sdlutils().images().at("weapons_arms"), 3, 3, 1, 0);
		weapon = addComponent<ChargeWeapon>(consts::CHARGE_TIER1_FIRERATE, consts::CHARGE_TIER1_DAMAGE);
		if (tierWeapon2 != 1) weapon->upgradeTier(tierWeapon2);
		weaponType = WeaponType::LASER;
	}
	else if (weaponType == WeaponType::LASER)
	{
		this->removeComponent<ChargeWeapon>();
		Component* img = addComponent<Image>(&sdlutils().images().at("weapons_arms"), 3, 3, 2, 0);
		weapon = addComponent<RicochetWeapon>(consts::RICOCHET_TIER1_FIRERATE, consts::RICOCHET_TIER1_DAMAGE, pl, 3, 1);
		if (tierWeapon3 != 1) weapon->upgradeTier(tierWeapon3);
		weaponType = WeaponType::RICOCHET;
	}
	else
	{
		this->removeComponent<RicochetWeapon>();
		Component* img = addComponent<Image>(&sdlutils().images().at("weapons_arms"), 3, 3, 0, 0);
		weapon = addComponent<Weapon>(consts::WEAPON_TIER1_FIRERATE, consts::WEAPON_TIER1_DAMAGE);
		if (tierWeapon1 != 1) weapon->upgradeTier(tierWeapon1);
		weaponType = WeaponType::CLASSIC;
	}
}

int WeaponBehaviour::tierOfWeapon()
{
	switch (weaponType) {
	case WeaponType::CLASSIC:
		return tierWeapon1;
		break;
	case WeaponType::LASER:
		return tierWeapon2;
		break;
	case WeaponType::RICOCHET:
		return tierWeapon3;
		break;
	}
}

void WeaponBehaviour::upgradeTier() {
	switch (weaponType) {
	case WeaponType::CLASSIC:
		tierWeapon1++;
		weapon->upgradeTier(tierWeapon1);
		break;

	case WeaponType::LASER:
		tierWeapon2++;
		weapon->upgradeTier(tierWeapon2);
		break;

	case WeaponType::RICOCHET:
		tierWeapon3++;
		weapon->upgradeTier(tierWeapon3);
		break;
	}
}