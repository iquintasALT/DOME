#pragma once

#include "../ecs/Component.h"
#include "../utils/checkML.h"
#include "../components/KeyboardPlayerCtrl.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include <math.h>


class Transform;
class Image;
class Player;
class WeaponAnimation;

enum class WeaponType;
enum ITEMS;
class Weapon : public Component
{
protected:
	Player* player_;
	RigidBody* playerRb_;
	Transform* playerTr_;
	Transform* tr_;
	KeyboardPlayerCtrl* playerCtrl_;
	Image* image_;
	WeaponAnimation* animator_;

	int impactDamage;
	bool flipped;

	float timeSinceLastShot;
	float fireRate; // minimum milliseconds between shots

	int magazineSize;
	int bulletsInReserve;

	float reloadTime;
	bool reloading;

	float baseBulletSpread;

	Texture* bulletTexture = &sdlutils().images().at("projectile");

	Vector2D calculateShotTrajectory(Vector2D direction); // Returns direction of the shot after accounting for random spread
	void calculatePosition();
	void calculateRotation(Vector2D& direction);
	virtual void shoot(Vector2D& direction);

public:
	Weapon(float rateOfFire, int damage, float crchBulletSpread = 0);

	~Weapon();
	bool ItemIsAmmo(Item* item, WeaponType weaponType);

	int bulletsInMagazine;
	inline virtual int getMagazineSize() { return magazineSize; }
	inline virtual int getAmmoReserves() { return bulletsInReserve; }
	virtual void init();

	void setAmmo();
	void setMaxAmmo();

	virtual void update();

	void reload();
	int getDamage() { return impactDamage; }
	void setDamage(int damage_) { impactDamage = damage_; }
	void setBulletSpread(int i) { baseBulletSpread = i; }

	void adjustToCrouching();
	virtual void upgradeTier(int tier);
};
