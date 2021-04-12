#include "weapon_behaviour.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Image.h"
#include "../components/Transform.h"
#include "../game/constant_variables.h"

WeaponBehaviour::WeaponBehaviour(Manager* mngr, Vector2D playerPos, Transform* playerTr , int typeOfWeapon) : GameEntity(mngr), weaponMovement(nullptr) {
	mngr->addEntity(this);
	mngr->addRenderLayer<Bullets>(this);

	addComponent<Transform>(Vector2D(playerPos.getX() + playerTr->getW() / 2, playerPos.getY() + playerTr->getW() * 0.4), 32, 32, 0);
	//3 TIERS PARA 3 ARMAS (REFACTORIZAR DE TAL FORMA QUE CADA ARMA SEPA CAMBIAR DE TIER)
	if (typeOfWeapon == 1) {
		addComponent<Image>(&sdlutils().images().at("weapons"), 3, 3, 0, 0);
		weaponMovement = addComponent<Weapon>(consts::WEAPON_TIER1_FIRERATE, consts::WEAPON_TIER1_DAMAGE);
	}
	else if(typeOfWeapon == 2) {
		Component* img = addComponent<Image>(&sdlutils().images().at("weapons"), 3, 3, 0, 1);
		weaponMovement = addComponent<Weapon>(consts::WEAPON_TIER2_FIRERATE, consts::WEAPON_TIER2_DAMAGE);
	}
	else if (typeOfWeapon == 3) {
		Component* img = addComponent<Image>(&sdlutils().images().at("weapons"), 3, 3, 0, 2);
		weaponMovement = addComponent<Weapon>(consts::WEAPON_TIER3_FIRERATE, consts::WEAPON_TIER3_DAMAGE);
	}
	else if (typeOfWeapon == 4) {
		Component* img = addComponent<Image>(&sdlutils().images().at("weapons"), 3, 3, 1, 0);
		weaponMovement = addComponent<ChargeWeapon>(consts::CHARGE_TIER1_FIRERATE, consts::CHARGE_TIER1_DAMAGE);
	}
	else if (typeOfWeapon == 5) {
		Component* img = addComponent<Image>(&sdlutils().images().at("weapons"), 3, 3, 1, 1);
		weaponMovement = addComponent<ChargeWeapon>(consts::CHARGE_TIER2_FIRERATE, consts::CHARGE_TIER2_DAMAGE);
	}
	else if (typeOfWeapon == 6) {
		Component* img = addComponent<Image>(&sdlutils().images().at("weapons"), 3, 3, 1, 2);
		weaponMovement = addComponent<ChargeWeapon>(consts::CHARGE_TIER3_FIRERATE, consts::CHARGE_TIER3_DAMAGE);
	}
	else if (typeOfWeapon == 7) {
		Component* img = addComponent<Image>(&sdlutils().images().at("weapons"), 3, 3, 2, 0);
		weaponMovement = addComponent<RicochetWeapon>(consts::RICOCHET_TIER1_FIRERATE, consts::RICOCHET_TIER1_DAMAGE, playerTr, 3, 1);
	}
	else if (typeOfWeapon == 8) {
		Component* img = addComponent<Image>(&sdlutils().images().at("weapons"), 3, 3, 2, 1);
		weaponMovement = addComponent<RicochetWeapon>(consts::RICOCHET_TIER2_FIRERATE, consts::RICOCHET_TIER2_DAMAGE, playerTr, 5, 2);
	}
	else if (typeOfWeapon == 9) {
		Component* img = addComponent<Image>(&sdlutils().images().at("weapons"), 3, 3, 2, 2);
		weaponMovement = addComponent<RicochetWeapon>(consts::RICOCHET_TIER3_FIRERATE, consts::RICOCHET_TIER3_DAMAGE, playerTr, 7, 3);
	}
}

Weapon* WeaponBehaviour::getWeaponMovement() {
	return weaponMovement;
}
