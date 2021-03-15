#include "player.h"

Player::Player(Manager* mngr_, Point2D pos) :GameCharacter(mngr_)
{
	mngr_->setHandler<Player_hdlr>(this);
	mngr_->addEntity(this);
	addComponent<Transform>(pos, Vector2D(), 32, 64, 0);
	addComponent<Image>(&sdlutils().images().at("player"), 2, 14, 0, 0);
	addComponent<player_animation>();
	addComponent<GravityComponent>();
	addComponent<KeyboardPlayerCtrl>();
 	addComponent<InventoryController>();

	Vector2D playerPos = getComponent<Transform>()->getPos();
	Transform* playerTr = getComponent<Transform>();
	//weapon = new WeaponBehaviour(3, 5, mngr_, playerPos, playerTr);
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