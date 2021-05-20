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
#include "../components/player_collisions.h"
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

Player::Player(Manager* mngr_, Point2D pos) : GameObject(mngr_)
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
	weapon->setInv(inv_);
	//weapon->getWeapon()->reload();


	physiognomy = new Physiognomy(this);
	addComponent<EnemyContactDamage>(physiognomy);
	setGroup<Player_grp>(true);
}

Player::Player(const Player* prevPlayer): GameObject(prevPlayer->mngr_)
{
	//TODO AÑADIR COMPONENTES
}

Player::~Player() {
	delete physiognomy;
}

WeaponBehaviour* Player::getCurrentWeapon() {
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
