#include "weapon_behaviour.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Image.h"
#include "../components/Transform.h"
#include "../components/weapon_animation.h"
#include "../game/constant_variables.h"

WeaponBehaviour::WeaponBehaviour(Manager* mngr, Vector2D playerPos, Transform* playerTr) : GameEntity(mngr), pl(playerTr), weapon(nullptr), animator_(nullptr) {
	mngr->addEntity(this);
	mngr->addRenderLayer<Bullets>(this);

	addComponent<Transform>(Vector2D(playerPos.getX() + playerTr->getW() / 2, playerPos.getY() + playerTr->getW() * 0.4), 38, 24, 0);

	addComponent<Image>(&sdlutils().images().at("weapons_arms"), 15, 8, 0, 0);
	animator_ = addComponent<WeaponAnimation>();
	weapon = addComponent<Weapon>(consts::WEAPON_TIER1_FIRERATE, consts::WEAPON_TIER1_DAMAGE, 0);
	weapon->bulletsInMagazine = 4;
	weaponType = Weapon::WeaponType::CLASSIC;
}

Weapon* WeaponBehaviour::getWeapon() {
	return weapon;
}

void WeaponBehaviour::changeWeapon()
{
	/*
	this->removeComponent<Image>();
	if (weaponType == WeaponType::CLASSIC)
	{
		weaponBullets[1] = getComponent<Weapon>()->bulletsInMagazine;
		this->removeComponent<Weapon>();
		animator_->setAnimation(ricochetWeaponTier);
		weapon = addComponent<RicochetWeapon>(consts::RICOCHET_TIER1_FIRERATE, consts::RICOCHET_TIER1_DAMAGE, 10.0, 3, 1);
		if (ricochetWeaponTier != 1) weapon->upgradeTier(ricochetWeaponTier);
		weaponType = WeaponType::RICOCHET;

		weapon->bulletsInMagazine = weaponBullets[2];

		if (weaponBullets <= 0)
			weapon->setAmmo();
	}
	else if (weaponType == WeaponType::RICOCHET)
	{
		weaponBullets[0] = getComponent<RicochetWeapon>()->bulletsInMagazine;
		this->removeComponent<RicochetWeapon>();
		animator_->setAnimation(0 + regularWeaponTier);
		weapon = addComponent<ChargeWeapon>(consts::CHARGE_TIER1_TIMETOCHARGE, consts::CHARGE_TIER1_DAMAGE);
		if (laserWeaponTier != 1) weapon->upgradeTier(laserWeaponTier);
		weaponType = WeaponType::LASER;

		weapon->bulletsInMagazine = weaponBullets[1];

		if (weaponBullets <= 0)
			weapon->setAmmo();
	}
	else
	{
		weaponBullets[2] = getComponent<ChargeWeapon>()->bulletsInMagazine;
		this->removeComponent<ChargeWeapon>();
		Component* img = addComponent<Image>(&sdlutils().images().at("weapons_arms"), 3, 3, 0, 0);
		weapon = addComponent<Weapon>(consts::WEAPON_TIER1_FIRERATE, consts::WEAPON_TIER1_DAMAGE);
		if (regularWeaponTier != 1) weapon->upgradeTier(regularWeaponTier);
		weaponType = WeaponType::CLASSIC;

		weapon->bulletsInMagazine = weaponBullets[0];

		if (weaponBullets <= 0)
			weapon->setAmmo();
	}*/
	weaponBullets[weaponType] = getComponent<Weapon>()->bulletsInMagazine;
	switch (weaponType)
	{
	case Weapon::WeaponType::CLASSIC:
		weaponType = Weapon::WeaponType::RICOCHET;
		weapon = addComponent2<Weapon, RicochetWeapon>(consts::RICOCHET_TIER1_FIRERATE, consts::RICOCHET_TIER1_DAMAGE, 10.0f, 3, weaponTiers[1]);
		break;
	case Weapon::WeaponType::RICOCHET:
		weaponType = Weapon::WeaponType::LASER;
		weapon = addComponent2<Weapon, ChargeWeapon>(consts::CHARGE_TIER1_TIMETOCHARGE, consts::CHARGE_TIER1_DAMAGE, weaponTiers[2], animator_);
		break;
	case Weapon::WeaponType::LASER:
		weaponType = Weapon::WeaponType::CLASSIC;
		weapon = addComponent<Weapon>(consts::WEAPON_TIER1_FIRERATE, consts::WEAPON_TIER1_DAMAGE);
		break;
	}
	animator_->setAnimation(weaponType * 3); 
	weapon->bulletsInMagazine = weaponBullets[weaponType];

	if (weaponBullets <= 0)
		weapon->setAmmo();
}

int WeaponBehaviour::tierOfWeapon()
{
	return weaponTiers[weaponType];
}

void WeaponBehaviour::upgradeCurrentWeapon() {
	++weaponTiers[weaponType];
	weapon->upgradeCurrentWeapon(weaponTiers[weaponType]);
}

void WeaponBehaviour::addDispersion(int i) {
	bulletSpread += i;
	weapon->setBulletSpread(bulletSpread);
}