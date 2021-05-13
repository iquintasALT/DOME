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
#include "../classes/player.h"

Weapon::Weapon(float fR, int dam, float bulletSpread) : bulletSpread(bulletSpread), fireRate(fR), flipped(false), playerCtrl_(nullptr), timeSinceLastShot(0), image_(nullptr), impactDamage(dam), player_(nullptr),
playerTr_(nullptr), tr_(nullptr)
{
	baseBulletSpread = bulletSpread;

	bulletsInReserve = 0;
	bulletsInMagazine = 0;
	magazineSize = 30;

	timeSinceLastShot = 0;
	reloadTime = 0;
	reloading = false;
	playerRb_ = nullptr;
}
Weapon::~Weapon() {}

void Weapon::update() {

	if (player_->getComponent<KeyboardPlayerCtrl>() != nullptr && player_->getComponent<KeyboardPlayerCtrl>()->isCrouching()) {
		bulletSpread = baseBulletSpread;
		if (baseBulletSpread - 20 >= 0)
			bulletSpread = baseBulletSpread - 20;
		else bulletSpread = 0;
	}
	else {
		bulletSpread = baseBulletSpread;
	}

	timeSinceLastShot += consts::DELTA_TIME;

	if (playerCtrl_->isStairs()) image_->enabled = false;
	else image_->enabled = true;

	Vector2D playerPos = playerTr_->getPos();
	if (flipped) tr_->setPos(Vector2D(playerPos.getX() + playerTr_->getW() * 0.56f, playerPos.getY() + playerTr_->getH() / 2.7f - tr_->getH() * 0.57));
	else tr_->setPos(Vector2D(playerPos.getX() + playerTr_->getW() * 0.17f, playerPos.getY() + playerTr_->getH() / 2.7f - tr_->getH() * 0.62));
	adjustToCrouching();

	Vector2D mousePos(ih().getMousePos().first, ih().getMousePos().second);

	mousePos = Camera::mainCamera->PointToWorldSpace(mousePos);

	Vector2D yCenteredPos(tr_->getPos().getX(), tr_->getPos().getY() + tr_->getH() * 0.37f); //Punto {0, Altura del ca��n}  
	Vector2D  dir = (mousePos - yCenteredPos).normalize();


	float radianAngle = atan2(dir.getY(), dir.getX());
	float degreeAngle = (radianAngle * 180.0) / M_PI;


	float playerX = playerPos.getX() + playerTr_->getW() / 2;
	float xDir = mousePos.getX() - playerX;

	if (!flipped && xDir < 0) {
		image_->setFlip(SDL_FLIP_VERTICAL);
		flipped = true;
	}
	else if (flipped && xDir > 0) {
		image_->setFlip(SDL_FLIP_NONE);
		flipped = false;
	}

	tr_->setRot(degreeAngle);

	if (ih().getMouseButtonState(InputHandler::LEFT) && timeSinceLastShot >= fireRate &&
		bulletsInMagazine > 0 && !reloading && !playerCtrl_->isStairs()) {

		timeSinceLastShot = 0;

		float maxSpread = bulletSpread; //Add here the dispersions
		if (!playerRb_->onFloor()) {
			maxSpread += 60;
		}
		float x = dir.getX(), y = dir.getY(), rotation = 0;
		if (maxSpread != 0)
			rotation = sdlutils().rand().nextInt(-maxSpread, maxSpread) * M_PI / 180.0;

		dir.setX(x * cos(rotation) - y * sin(rotation));
		dir.setY(x * sin(rotation) + y * cos(rotation));

		Entity* bullet = entity_->getMngr()->addEntity();

		Transform* bulletTr = bullet->addComponent<Transform>(Vector2D(), 4, 6, 0);
		RigidBody* rb = bullet->addComponent<RigidBody>(dir * 10.0, false);

		float aux1 = tr_->getW() - 8; //Distancia del ca��n del arma para spawnear la bala
		float aux2 = tr_->getPos().getY() + tr_->getH() / 2 - yCenteredPos.getY();

		float offsetX = sin(-radianAngle) * aux2;
		float offsetY = cos(-radianAngle) * aux2;
		if (flipped) {
			offsetX = -offsetX;
			offsetY = -offsetY;
		}

		Vector2D centeredPos = { yCenteredPos.getX() - bulletTr->getW() / 2 - offsetX, tr_->getPos().getY() + tr_->getH() / 2 - bulletTr->getH() / 2 - offsetY }; //Punto para spawnear la bala centrada

		bulletTr->setPos(centeredPos + dir * aux1);
		bulletTr->setRot(degreeAngle);

		entity_->getMngr()->addRenderLayer<Bullets>(bullet);
		bullet->addComponent<Image>(&sdlutils().images().at("projectile"));
		bullet->addComponent<ClassicBullet>();

		bulletsInMagazine--;

		if (bulletsInMagazine <= 0)
		{
			reload();
		}
	}
	if (reloading)
	{
		reloadTime += consts::DELTA_TIME;
	}
	if (reloadTime > 2.0) //Tiempo de recarga en segundos
	{
		reloadTime = 0;
		reloading = false;
	}
}

void Weapon::setMaxAmmo() {
	int totalBullets = 0;
	Item* item = nullptr;

	WeaponType currentWeapon = player_->getCurrentWeapon()->typeOfWeapon();
	for (auto items : player_->getComponent<InventoryController>()->inventory->getItems()) {
		if (ItemIsAmmo(items, currentWeapon)) {
			item = items;
			totalBullets += item->count;
		}
	}

	if (item != nullptr) {
		bulletsInReserve = totalBullets;
	}
}

void Weapon::setAmmo() {
	int totalBullets = 0;
	Item* item = nullptr;
	WeaponType currentWeapon = player_->getCurrentWeapon()->typeOfWeapon();

	for (auto items : player_->getComponent<InventoryController>()->inventory->getItems()) {
		if (ItemIsAmmo(items, currentWeapon)) {
			item = items;
			totalBullets += item->count;
		}
	}

	if (item != nullptr) {
		bulletsInMagazine = item->count;
		bulletsInReserve = totalBullets - item->count;

		player_->getComponent<InventoryController>()->inventory->removeItem(item);
		delete item;
		item = nullptr;
	}
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


void Weapon::reload()
{
	if (!reloading && bulletsInMagazine < magazineSize)
	{
		reloading = true;
		setAmmo();
	}
}

void Weapon::adjustToCrouching() {
	if (player_->getComponent<KeyboardPlayerCtrl>() != nullptr && player_->getComponent<KeyboardPlayerCtrl>()->isCrouching())
		tr_->setPos(Vector2D(tr_->getPos().getX(), tr_->getPos().getY() + playerTr_->getH() * 0.3f));
}

void Weapon::init()
{
	player_ = static_cast<Player*>(entity_->getMngr()->getHandler<Player_hdlr>());
	playerTr_ = player_->getComponent<Transform>();
	tr_ = entity_->getComponent <Transform>();
	playerCtrl_ = player_->getComponent<KeyboardPlayerCtrl>();
	assert(tr_ != nullptr && playerTr_ != nullptr && playerCtrl_ != nullptr);

	image_ = entity_->getComponent<Image>();
	assert(image_ != nullptr);
	image_->setRotationOrigin(tr_->getW() * 0.16f, tr_->getH() * 0.46f);

	playerRb_ = player_->getComponent<RigidBody>();
	assert(playerRb_ != nullptr);
}

void Weapon::upgradeTier(int tier) {
	if (tier == 2) {
		entity_->removeComponent<Image>();
		entity_->addComponent<Image>(&sdlutils().images().at("weapons_arms"), 3, 3, 0, 1);
		impactDamage = consts::WEAPON_TIER2_DAMAGE;
		fireRate = consts::WEAPON_TIER2_FIRERATE;
	}
	else if (tier == 3) {
		entity_->removeComponent<Image>();
		entity_->addComponent<Image>(&sdlutils().images().at("weapons_arms"), 3, 3, 0, 2);
		impactDamage = consts::WEAPON_TIER3_DAMAGE;
		fireRate = consts::WEAPON_TIER3_FIRERATE;
	}
}