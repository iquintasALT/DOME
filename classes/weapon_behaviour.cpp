#include "weapon_behaviour.h"

WeaponBehaviour::WeaponBehaviour(float fireRate, float dmg, Manager* mngr, Vector2D playerPos, Transform* playerTr) : GameEntity(mngr) {
	mngr->addEntity(this);
	addComponent<Transform>(Vector2D(playerPos.getX() + playerTr->getW() / 2, playerPos.getY() + playerTr->getW() * 0.4), Vector2D(), 32, 32, 0);
	addComponent<Image>(&sdlutils().images().at("weapons"), 3, 3, 2, 2);
	addComponent<Weapon>(fireRate);
	dmg_ = dmg;
}