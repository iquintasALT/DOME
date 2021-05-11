#include "weapon.h"
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../game/constant_variables.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../components/Image.h"
#include "../components/Transform.h"
#include "../sdlutils/SDLUtils.h"
#include "../classes/camera.h"
#include "../components/ricochet.h"
#include "../components/classic_bullet.h"
#include "../components/rigid_body.h"
#include "../game/constant_variables.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/rigid_body.h"
#include "../components/Inventory.h"
#include "../components/InventoryController.h"
#include "../classes/weapon_behaviour.h"
#include "../classes/Item.h"
#include <iostream>

Weapon::Weapon(float fR, int dam, float dispersion) : dispersion(dispersion), fireRate(fR), flipped(false), ctrl(nullptr), shootTime(0), entityImg(nullptr), damage(dam), player(nullptr),
playerTr(nullptr), entityTr(nullptr)
{
	remainingBullets = 0;
	currentCharger = nullptr;
	chargerSize = 30;

	shootTime = 0;
	rechargeTime = 0;
	recharging = false;
	playerRb = nullptr;
}
Weapon::~Weapon() {}

int Weapon::getChargerBullets()
{
	return currentCharger->count;
}

void Weapon::update() {
	shootTime += consts::DELTA_TIME;

	if (ctrl->isStairs()) entityImg->enabled = false;
	else entityImg->enabled = true;

	Vector2D playerPos = playerTr->getPos();
	if (flipped) entityTr->setPos(Vector2D(playerPos.getX() + playerTr->getW() / 1.25, playerPos.getY() + playerTr->getH() / 2.75f - entityTr->getH() / 2));
	else entityTr->setPos(Vector2D(playerPos.getX() + playerTr->getW() / 4, playerPos.getY() + playerTr->getH() / 2.75f - entityTr->getH() / 2));
	adjustToCrouching();

	Vector2D mousePos(ih().getMousePos().first, ih().getMousePos().second);

	mousePos = Camera::mainCamera->PointToWorldSpace(mousePos);

	Vector2D yCenteredPos(entityTr->getPos().getX(), entityTr->getPos().getY() + entityTr->getH() * 0.37f); //Punto {0, Altura del ca��n}  
	Vector2D  dir = (mousePos - yCenteredPos).normalize();


	float radianAngle = atan2(dir.getY(), dir.getX());
	float degreeAngle = (radianAngle * 180.0) / M_PI;

	if (!flipped && (degreeAngle > 90 || degreeAngle < -90)) {
		entityImg->setFlip(SDL_FLIP_VERTICAL);
		flipped = true;
	}
	else if (flipped && degreeAngle < 90 && degreeAngle > -90) {
		entityImg->setFlip(SDL_FLIP_NONE);
		flipped = false;
	}

	entityTr->setRot(degreeAngle);

	if (ih().getMouseButtonState(InputHandler::LEFT) && shootTime >= fireRate &&
		currentCharger != nullptr && currentCharger->count > 0 && !recharging && !ctrl->isStairs()) {

		shootTime = 0;

		float maxDispersion = dispersion; //Add here the dispersions
		if (!playerRb->onFloor()) {
			maxDispersion += 60;
		}
		float x = dir.getX();
		float y = dir.getY();
		float rotation = 0;
		if (maxDispersion != 0)
			rotation = sdlutils().rand().nextInt(-maxDispersion, maxDispersion) * M_PI / 180.0;

		dir.setX(x * cos(rotation) - y * sin(rotation));
		dir.setY(x * sin(rotation) + y * cos(rotation));

		Entity* bullet = entity_->getMngr()->addEntity();

		Transform* bulletTr = bullet->addComponent<Transform>(Vector2D(), 4, 6, 0);
		RigidBody* rb = bullet->addComponent<RigidBody>(dir * 10.0, false);

		float aux1 = entityTr->getW() - 8; //Distancia del ca��n del arma para spawnear la bala
		float aux2 = entityTr->getPos().getY() + entityTr->getH() / 2 - yCenteredPos.getY();

		float offsetX = sin(-radianAngle) * aux2;
		float offsetY = cos(-radianAngle) * aux2;
		if (flipped) {
			offsetX = -offsetX;
			offsetY = -offsetY;
		}

		Vector2D centeredPos = { yCenteredPos.getX() - bulletTr->getW() / 2 - offsetX  ,entityTr->getPos().getY() + entityTr->getH() / 2 - bulletTr->getH() / 2 - offsetY }; //Punto para spawnear la bala centrada

		bulletTr->setPos(centeredPos + dir * aux1);
		bulletTr->setRot(degreeAngle);

		entity_->getMngr()->addRenderLayer<Bullets>(bullet);
		bullet->addComponent<Image>(&sdlutils().images().at("projectile"));
		bullet->addComponent<ClassicBullet>();

		currentCharger->count--;

		if (currentCharger == 0)
		{
			recharge();
		}
	}
	if (recharging)
	{
		rechargeTime += consts::DELTA_TIME;
	}
	if (rechargeTime > 2.0) //Tiempo de recarga en segundos
	{
		rechargeTime = 0;
		recharging = false;
	}
}

void Weapon::setAmmo() {

}

bool Weapon::ItemIsAmmo(Item* item, WeaponType currentWeapon) {
	ITEMS itemType = item->getItemInfo()->name();
	switch (currentWeapon) {
	case WeaponType::CLASSIC:
		return itemType == ITEMS::CLASSIC_AMMO;
	case WeaponType::LASER:
		return itemType == ITEMS::LASER_AMMO;
	case WeaponType::RICOCHET:
		return itemType == ITEMS::RICOCHET_AMMO;
		break;
	default:
		return false;
		break;
	}
}


void Weapon::recharge()
{
	if (!recharging && remainingBullets > 0 && currentCharger->count < chargerSize)
	{
		recharging = true;

		int totalBullets = 0;
		Item* item = nullptr;
		//WeaponType currentWeapon = entity_->getComponent<WeaponBehaviour>()->typeOfWeapon();
		/*for (auto items : entity_->getComponent<InventoryController>()->inventory->getItems()) {
			if (ItemIsAmmo(items, currentWeapon)) {
				item = items;
				totalBullets += item->count;
			}
		}*/

		if (item != nullptr){
			remainingBullets = totalBullets - item->count;
		}
	}
}

void Weapon::adjustToCrouching() {
	if (player->getComponent<KeyboardPlayerCtrl>() != nullptr && player->getComponent<KeyboardPlayerCtrl>()->isCrouching())
		entityTr->setPos(Vector2D(entityTr->getPos().getX(), entityTr->getPos().getY() + playerTr->getH() * 0.3f));
}

void Weapon::init()
{
	player = entity_->getMngr()->getHandler<Player_hdlr>();
	playerTr = player->getComponent<Transform>();
	entityTr = entity_->getComponent <Transform>();
	ctrl = player->getComponent<KeyboardPlayerCtrl>();
	assert(entityTr != nullptr && playerTr != nullptr && ctrl != nullptr);

	entityImg = entity_->getComponent<Image>();
	assert(entityImg != nullptr);
	entityImg->setRotationOrigin(0, entityTr->getH() / 2);

	playerRb = player->getComponent<RigidBody>();
	assert(playerRb != nullptr);
}

void Weapon::upgradeTier(int tier) {
	if (tier == 2) {
		entity_->removeComponent<Image>();
		entity_->addComponent<Image>(&sdlutils().images().at("weapons_arms"), 3, 3, 0, 1);
		damage = consts::WEAPON_TIER2_DAMAGE;
		fireRate = consts::WEAPON_TIER2_FIRERATE;
	}
	else if (tier == 3) {
		entity_->removeComponent<Image>();
		entity_->addComponent<Image>(&sdlutils().images().at("weapons_arms"), 3, 3, 0, 2);
		damage = consts::WEAPON_TIER3_DAMAGE;
		fireRate = consts::WEAPON_TIER3_FIRERATE;
	}
}