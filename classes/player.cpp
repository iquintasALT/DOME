#include "player.h"

Player::Player(Manager* mngr_, Point2D pos) :GameCharacter(mngr_)
{
	mngr_->setHandler<Player_hdlr>(this);
	mngr_->addEntity(this);
	addComponent<Transform>(Point2D(), Vector2D(), 32, 64, 0);
	addComponent<Image>(&sdlutils().images().at("player"), 2, 14, 0, 0);
	addComponent<player_animation>();
	addComponent<GravityComponent>();
	addComponent<KeyboardPlayerCtrl>();
	addComponent<InventoryController>();
	weapon = addComponent<WeaponBehaviour>();
}

WeaponBehaviour* Player::equipWeapon(WeaponBehaviour* newWeapon)
{
	WeaponBehaviour* oldWeapon = weapon;
	*getComponent<WeaponBehaviour>() = *newWeapon;
	return oldWeapon;
}