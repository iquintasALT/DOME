#include "player.h"
#include "../classes/weapon_behaviour.h"
#include "../sdlutils/SDLUtils.h"
#include "../game/ecs_defs.h"
#include "../ecs/Manager.h"
#include "../components/Transform.h"
#include "../components/player_animation.h"
#include "../components/GravityComponent.h"
#include "../components/Image.h"
#include "../components/KeyboardPlayerCtrl.h"
#include "../components/InventoryController.h"
#include "../components/weapon.h"
#include "../components/interactions.h"
#include "../components/player_collisions.h"
#include "../classes/particleSystem.h"

Player::Player(Manager* mngr_, Point2D pos) :GameCharacter(mngr_)
{
	mngr_->setHandler<Player_hdlr>(this);
	mngr_->addEntity(this);
	Transform* t = addComponent<Transform>(pos, Vector2D(), 32, 64, 0);
	addComponent<Image>(&sdlutils().images().at("player"), 3, 14, 0, 0);
	addComponent<ParticleSystem>(&sdlutils().images().at("dust"), 1, 1, 0, 0);
	addComponent<GravityComponent>();
	addComponent<KeyboardPlayerCtrl>();
	addComponent<player_animation>();
	addComponent<Interactions>();
	addComponent<PlayerCollisions>(mngr_);

	Vector2D playerPos = t->getPos();
	weapon = new WeaponBehaviour(2, 5, mngr_, playerPos, t,4);

	addComponent<InventoryController>();
}


WeaponBehaviour* Player::getCurrentWeapon() {
	return weapon;
}

WeaponBehaviour* Player::equipWeapon(WeaponBehaviour* newWeapon)
{
	WeaponBehaviour* oldWeapon = weapon;
	weapon = newWeapon;
	return oldWeapon;
}