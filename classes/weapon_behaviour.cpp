#include "weapon_behaviour.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Image.h"
#include "../components/Transform.h"
#include "../components/weapon_animation.h"
#include "../game/constant_variables.h"

WeaponBehaviour::WeaponBehaviour(Manager* mngr, Vector2D playerPos, Transform* playerTr) : Entity(mngr), pl(playerTr), weapon(nullptr), animator_(nullptr), inv_(nullptr) {
	mngr->addEntity(this);
	mngr->addRenderLayer<Bullets>(this);

	addComponent<Transform>(Vector2D(playerPos.getX() + playerTr->getW() / 2, playerPos.getY() + playerTr->getW() * 0.4), 55, 48, 0);

	addComponent<Image>(&sdlutils().images().at("weapons_arms"), 15, 8, 0, 0)->setRotationOrigin(4, 25);

	animator_ = addComponent<WeaponAnimation>();
	weapon = addComponent<Weapon>(consts::WEAPON_TIER1_FIRERATE, consts::WEAPON_TIER1_DAMAGE, 0);
	weaponType = Weapon::WeaponType::CLASSIC;
}

Weapon* WeaponBehaviour::getWeapon() {
	return weapon;
}

void WeaponBehaviour::changeWeapon()
{
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
	animator_->setAnimation(weaponType * 3 + weaponTiers[weaponType]); 

	//if (weapon->getBulletsInMagazine() <= 0)
		//weapon->reload();
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