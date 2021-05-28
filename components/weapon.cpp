#include "weapon.h"
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/SoundManager.h"
#include "../game/constant_variables.h"
#include "../classes/camera.h"
#include "../classes/weapon_behaviour.h"
#include "../classes/item.h"
#include "../classes/player.h"
#include "image.h"
#include "transform.h"
#include "ricochet.h"
#include "classic_bullet.h"
#include "rigid_body.h"
#include "inventory.h"
#include "inventory_controller.h"
#include "weapon_animation.h"
#include <iostream>
#include <list>

int Weapon::bulletsInMagazine = -1;

Weapon::Weapon(float bulletSpread, int tier) : baseBulletSpread(bulletSpread), tier_(tier) {}

Weapon::~Weapon() {}

void Weapon::calculatePosition() {
	Vector2D playerPos = playerTr_->getPos();
	if (flipped) tr_->setPos(Vector2D(playerPos.getX() + playerTr_->getW() * 0.58f, playerPos.getY() + playerTr_->getH() / 2.7f - tr_->getH() * 0.62));
	else tr_->setPos(Vector2D(playerPos.getX() + playerTr_->getW() * 0.21f, playerPos.getY() + playerTr_->getH() / 2.7f - tr_->getH() * 0.62));
	adjustToCrouching();
}

Point2D Weapon::calculateBulletPosition(const Vector2D& direction) {
	Point2D pos = tr_->getPos() + Vector2D(tr_->getW() - 11, tr_->getH() * 0.45); // point at end of gun without rotation
	Point2D rotationPin = image_->getOriginInWorld(tr_);
	Point2D lengthOfGun = pos - rotationPin; // position of end of gun relative to rotation origin
	pos = rotationPin + direction.normalize() * lengthOfGun.magnitude();
	return pos;
}

Vector2D Weapon::calculateShotTrajectory(Vector2D direction) {
	// If crouching, reduce spread by 20 but no lower than 0, otherwise use regular spread
	float bulletSpread = playerCtrl_->isCrouching() ? std::max(baseBulletSpread - 20, 0.0f) : baseBulletSpread;

	if (playerCtrl_->isWalking())
		bulletSpread += 10;

	float maxSpread = bulletSpread;

	// Increase spread cone if player is airborne
	if (!playerRb_->onFloor()) maxSpread += 60;

	float offset = 0;
	// If there is any spread range, generate a random angle within that range
	if (maxSpread != 0)
		offset = sdlutils().rand().nextInt(-maxSpread, maxSpread) * M_PI / 180.0;

	// Final direction is equal to aim direction rotated by offset
	direction.setX(direction.getX() * cos(offset) - direction.getY() * sin(offset));
	direction.setY(direction.getX() * sin(offset) + direction.getY() * cos(offset));

	return direction;
}

void Weapon::calculateRotation(Vector2D& direction) {

	// Position of mouse in world coordinates
	Vector2D mousePos = Camera::mainCamera->PointToWorldSpace(Vector2D(ih().getMousePos().first, ih().getMousePos().second));

	Vector2D yCenteredPos(tr_->getPos().getX(), tr_->getPos().getY() + tr_->getH() * 0.5f); //Punto {0, Altura del ca��n}  
	direction = (mousePos - yCenteredPos).normalize();

	float radianAngle = atan2(direction.getY(), direction.getX());
	float degreeAngle = (radianAngle * 180.0) / M_PI;

	float playerX = playerTr_->getPos().getX() + playerTr_->getW() / 2;
	float xDir = mousePos.getX() - playerX;

	// Flip image if required
	if (!flipped && xDir < 0) {
		image_->setFlip(SDL_FLIP_VERTICAL);
		flipped = true;
	}
	else if (flipped && xDir > 0) {
		image_->setFlip(SDL_FLIP_NONE);
		flipped = false;
	}

	// Apply rotation
	tr_->setRot(degreeAngle);
}

Entity* Weapon::createBullet(const Vector2D& direction)
{
	Entity* bullet = entity_->getMngr()->addEntity();
	bullet->addComponent<Transform>(Vector2D(), 4, 6, 0);
	bullet->addComponent<RigidBody>(direction * 10.0, false);
	bullet->addComponent<Image>(bulletTexture_);
	bullet->addComponent<ClassicBullet>();
	entity_->getMngr()->addRenderLayer<Bullets>(bullet);
	return bullet;
}

void Weapon::shoot(const Vector2D& direction) {
	timeSinceLastShot = 0;

	Entity* bullet = createBullet(calculateShotTrajectory(direction));

	Transform* bulletTr = bullet->getComponent<Transform>();
	RigidBody* rb = bullet->getComponent<RigidBody>();

	bulletTr->setPos(calculateBulletPosition(direction));
	bulletTr->setRot(tr_->getRot());

	setBulletsInMagazine(getBulletsInMagazine() - 1);

	if (getBulletsInMagazine() <= 0)
		reload();
	switch (type)
	{
	case Weapon::CLASSIC:
		soundManager().playSFX("normalgun");
		break;
	case Weapon::RICOCHET:
		soundManager().playSFX("ricochetShot");
		break;
	case Weapon::LASER:
		soundManager().playSFX("laserShot");
		break;
	default:
		break;
	}
}

void Weapon::update() {

	if (!playerCtrl_->isClimbingLadder())
	{
		if (!image_->enabled) image_->enabled = true;

		timeSinceLastShot += consts::DELTA_TIME;

		calculatePosition();

		Vector2D rotation = Vector2D();
		calculateRotation(rotation);
		if (reloading)
		{
			reloadTime += consts::DELTA_TIME;
			if (reloadTime > 2.0) //Tiempo de recarga en segundos
			{
				reloadTime = 0;
				reloading = false;
			}
		}
		else if (ih().getMouseButtonState(InputHandler::LEFT) && timeSinceLastShot >= fireRate &&
			getBulletsInMagazine() > 0 && !reloading)
			shoot(rotation);
	}
	else
		image_->enabled = false;
}

void Weapon::setMaxAmmo() {
	int totalBullets = 0;
	Item* item = nullptr;

	WeaponType currentWeapon = player_->getWeapon()->typeOfWeapon();
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
	std::vector<Item*> items = std::vector<Item*>();
	for (auto item : player_->getComponent<InventoryController>()->inventory->getItems()) {
		if (ItemIsAmmo(item, type)) {
			items.push_back(item);
			totalBullets += item->count;
		}
	}

	/// por si acaso hay objetos de balas con menos balas restantes que el tamaño del cargador,
	/// vamos a seguir vaciando más items hasta que se llene el cargador (o no queden items)
	while (getBulletsInMagazine() < magazineSize && items.size() > 0) {
		// cogemos balas del último objeto cargador
		int ammoPulled = std::min(items[items.size() - 1]->count, magazineSize - getBulletsInMagazine());
		setBulletsInMagazine(getBulletsInMagazine() + ammoPulled);
		bulletsInReserve = totalBullets - ammoPulled;

		items[items.size() - 1]->count -= ammoPulled;

		if (items[items.size() - 1]->count == 0) //solo tenemos que borrar el stack de municion si lo hemos vaciado
		{
			player_->getComponent<InventoryController>()->inventory->removeItem(items[items.size() - 1]);
			items.pop_back();
		}
	}

	if (totalBullets != 0) soundManager().playSFX("reload");
	else soundManager().playSFX("empty_clip");
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
	if (!reloading && getBulletsInMagazine() < magazineSize)
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

	playerRb_ = player_->getComponent<RigidBody>();
	assert(playerRb_ != nullptr);

	fireRate = consts::WEAPON_FIRERATES[3 * type + tier_];
	impactDamage = consts::WEAPON_DAMAGE_VALUES[3 * type + tier_];
	magazineSize = consts::WEAPON_MAGAZINE_SIZES[3 * type + tier_];
}