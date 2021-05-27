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

	addComponent<Image>(&sdlutils().images().at("weapons_arms"), 15, 8, 0, 0)->setRotationOrigin(4, 24);

	animator_ = addComponent<WeaponAnimation>();
	weaponType = Weapon::WeaponType::CLASSIC;
	weapon = addComponent<Weapon>(0, weaponTiers[weaponType]);
}

WeaponBehaviour::~WeaponBehaviour()
{
	Entity::~Entity();
}

Weapon* WeaponBehaviour::getCurrentWeapon() {
	return weapon;
}

void WeaponBehaviour::changeWeapon()
{
	switch (weaponType)
	{
	case Weapon::WeaponType::CLASSIC:
		weaponType = Weapon::WeaponType::RICOCHET;
		weapon = addComponent2<Weapon, RicochetWeapon>(10.0f, 3, weaponTiers[1]);
		break;
	case Weapon::WeaponType::RICOCHET:
		weaponType = Weapon::WeaponType::LASER;
		weapon = addComponent2<Weapon, ChargeWeapon>(weaponTiers[2], animator_);
		break;
	case Weapon::WeaponType::LASER:
		weaponType = Weapon::WeaponType::CLASSIC;
		weapon = addComponent<Weapon>(0, weaponTiers[0]);
		break;
	}
	animator_->setAnimation(weaponType * 3 + weaponTiers[weaponType]); 

	if (weapon->getBulletsInMagazine() <= 0)
		weapon->setAmmo();
}

void WeaponBehaviour::updateWeapons(short int* newTiers)
{
	for (int i = 0; i < 3; i++)
		weaponTiers[i] = newTiers[i];
}

int WeaponBehaviour::tierOfWeapon()
{
	return weaponTiers[weaponType];
}

void WeaponBehaviour::upgradeCurrentWeapon() {
	++weaponTiers[weaponType];
}

void WeaponBehaviour::addDispersion(int i) {
	bulletSpread += i;
	weapon->setBulletSpread(bulletSpread);
}