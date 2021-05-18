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

enum ITEMS;

class Weapon : public Component
{
private:
	static int bulletsInMagazine;

protected:
	Transform* tr_ = nullptr;
	Image* image_ = nullptr;
	Player* player_ = nullptr;
	RigidBody* playerRb_ = nullptr;
	Transform* playerTr_ = nullptr;
	KeyboardPlayerCtrl* playerCtrl_ = nullptr;

	int impactDamage;
	bool flipped = false;

	float timeSinceLastShot = 0;
	float fireRate; // minimum milliseconds between shots

	int magazineSize;
	int bulletsInReserve = 0;

	float reloadTime = 0;
	bool reloading = false; 

	float baseBulletSpread;

	Texture* bulletTexture_ = &sdlutils().images().at("projectile");

	Vector2D calculateShotTrajectory(Vector2D direction); // Returns direction of the shot after accounting for random spread
	void calculatePosition();
	void calculateRotation(Vector2D& direction);
	virtual Entity* createBullet(const Vector2D& direction);
	virtual void shoot(const Vector2D& direction);

public:
	enum WeaponType { CLASSIC, RICOCHET, LASER };
	WeaponType type = CLASSIC;

	Weapon() {};
	Weapon(float rateOfFire, int damage, float bulletSpread = 0, int tier = 0);
	~Weapon();

	bool ItemIsAmmo(Item* item, WeaponType weaponType);

	inline virtual int getMagazineSize() { return magazineSize; }
	inline virtual int getAmmoReserves() { return bulletsInReserve; }
	int getDamage() { return impactDamage; }
	virtual int getAnimationRow() { return type; };
	virtual int getBulletsInMagazine() { return bulletsInMagazine; };
	 
	void setAmmo();
	void setMaxAmmo();
	void setDamage(int damage_) { impactDamage = damage_; }
	void setBulletSpread(int i) { baseBulletSpread = i; }
	virtual void setBulletsInMagazine(int bullets) { bulletsInMagazine = bullets; };

	virtual void update();

	virtual void reload();

	void adjustToCrouching();
	virtual void upgradeCurrentWeapon(int tier);

	virtual void init();
};
