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

	weapon = mngr_->addEntity();
	Vector2D playerPos = getComponent<Transform>()->getPos();
	Transform* playerTr = getComponent<Transform>();
	weapon->addComponent<Transform>(Vector2D(playerPos.getX() + playerTr->getW() / 2, playerPos.getY() + playerTr->getW() * 0.4), Vector2D(), 32, 32, 0);
	weapon->addComponent<Image>(&sdlutils().images().at("weapons"), 3, 3, 2, 2);
	weapon->addComponent<WeaponBehaviour>(); 
}

WeaponBehaviour* Player::equipWeapon(WeaponBehaviour* newWeapon)
{
	WeaponBehaviour* oldWeapon = weapon->getComponent<WeaponBehaviour>();
	*getComponent<WeaponBehaviour>() = *newWeapon;
	return oldWeapon;
}