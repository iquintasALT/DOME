#include "player.h"

#include "../sdlutils/SDLUtils.h"

#include "../ecs/Manager.h"

#include "../components/Transform.h"
#include "../components/player_animation.h"
#include "../components/Image.h"
#include "../components/KeyboardPlayerCtrl.h"
#include "../components/InventoryController.h"
#include "../components/weapon.h"
#include "../components/interactions.h"
#include "../components/particleSystem.h"
#include "../components/bleedout_component.h"
#include "../components/pain_component.h"
#include "../components/concussion_component.h"
#include "../components/intoxication_component.h"
#include "../components/hunger_component.h"
#include "../components/tiredness_component.h"
#include "../components/hypothermia_component.h"
#include "../components/box_collider.h"
#include "../components/CameraMovement.h"
#include "../components/enemy_contact_damege.h"

#include "../classes/weapon_behaviour.h"
#include "../classes/physiognomy.h"

Player::Player(Manager* mngr_, Point2D pos) : Entity(mngr_)
{
	mngr_->addEntity(this);
	mngr_->setHandler<Player_hdlr>(this);
	Transform* t = addComponent<Transform>(pos, 32, 64);
	addComponent<Image>(&sdlutils().images().at("player"), 10, 14, 0, 0);
	mngr_->addRenderLayer<Player>(this);
	addComponent<ParticleSystem>(&sdlutils().images().at("dust"), 1, 1, 0, 0);
	addComponent<BoxCollider>();
	addComponent<RigidBody>();
	addComponent<KeyboardPlayerCtrl>();
	addComponent<player_animation>();
	addComponent<Interactions>();
	addComponent<HungerComponent>();
	addComponent<TirednessComponent>();
	addComponent<CameraMovement>(.7);

	weapon = new WeaponBehaviour(mngr_, t->getPos(), t);
	auto inv_ = addComponent<InventoryController>();
	inv_->inventory->isPlayer = true;
	weapon->setInv(inv_);
	//weapon->getWeapon()->reload();

	physiognomy = new Physiognomy(this);
	addComponent<EnemyContactDamage>(physiognomy);
	setGroup<Player_grp>(true);

	mngr_->getGame()->playerSaved = this;
	mngr_->getGame()->playerCreated = true;

	weapon->getWeapon()->setAmmo();
}

Player::Player(Player* prevPlayer, Manager* mngr):
	Player(mngr, prevPlayer->getComponent<Transform>()->getPos())
{
	//Componentes a copiar:
	//Inventario, Weapon,  physionomy
	//Me dicen que physionomia no
//======================================================================================

	Inventory* oldInv = prevPlayer->getComponent<InventoryController>()->inventory;
	Inventory* newInv = this->getComponent<InventoryController>()->inventory;
	
	for (auto item : newInv->getItems()) {
		delete item;
	}
	newInv->getItems().clear();

	for (auto item : oldInv->getItems()) {
		newInv->storeItem(new Item(item, newInv));
	}
	oldInv->getItems().clear();

//======================================================================================

	WeaponBehaviour* oldWeapon = prevPlayer->getWeapon();
	WeaponBehaviour* newWeapon = this->getWeapon();

	for (int i = 0; i < 3; i++) {
		int weaponTier = oldWeapon->tierOfWeapon();
		for (int tier = 0; tier < weaponTier; tier++) {
			newWeapon->upgradeCurrentWeapon();
		}
		newWeapon->changeWeapon();
	}

//======================================================================================

	//Faltaria la fisionomia si es que la hacemos que se guarde al final

//======================================================================================

	delete prevPlayer;
}

Player::~Player() {
	delete physiognomy;
	delete weapon;
	delete getComponent<InventoryController>()->inventory;
}

WeaponBehaviour* Player::getWeapon() {
	return weapon;
}

WeaponBehaviour* Player::equipWeapon(WeaponBehaviour* newWeapon) {
	WeaponBehaviour* oldWeapon = weapon;
	weapon = newWeapon;
	return oldWeapon;
}

Physiognomy* Player::getPhysiognomy() {
	return physiognomy;
}
