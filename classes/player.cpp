#include "player.h"
#include "../classes/weapon_behaviour.h"
#include "../sdlutils/SDLUtils.h"
#include "../game/ecs_defs.h"
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
#include "../classes/physiognomy.h"
#include "../components/bleedout_component.h"
#include "../components/pain_component.h"
#include "../components/concussion_component.h"
#include "../components/intoxication_component.h"
#include "../components/hunger_component.h"
#include "../components/tiredness_component.h"
#include "../components/hypothermia_component.h"
#include "../components/box_collider.h"

Player::Player(Manager* mngr_, Point2D pos) : GameCharacter(mngr_)
{
	mngr_->setHandler<Player_hdlr>(this);
	mngr_->addEntity(this);
	Transform* t = addComponent<Transform>(pos, 32, 64);
	addComponent<Image>(&sdlutils().images().at("player"), 6, 14, 0, 0);
	mngr_->addRenderLayer<Player>(this);
	addComponent<ParticleSystem>(&sdlutils().images().at("dust"), 1, 1, 0, 0);
	addComponent<BoxCollider>();
	addComponent<RigidBody>();
	addComponent<KeyboardPlayerCtrl>();
	addComponent<player_animation>();
	addComponent<Interactions>();
	addComponent<HungerComponent>();
	addComponent<TirednessComponent>();
	
	weapon = new WeaponBehaviour(mngr_, t->getPos(), t, 5);
	addComponent<InventoryController>();

	physiognomy = new Physiognomy(this);
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
