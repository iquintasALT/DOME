#include "ricochet_weapon.h"
#include "../utils/Vector2D.h"
#include "../components/Transform.h"
#include "../sdlutils/InputHandler.h"
#include "../classes/camera.h"
#include "../components/Image.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../game/constant_variables.h"
#include "../components/ricochet.h"
#include "../game/constant_variables.h"

#include "../classes/Item.h"
void RicochetWeapon::update() {

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

	if (playerCtrl_->isClimbingLadder()) entityImg->enabled = false;
	else entityImg->enabled = true;

	Vector2D playerPos = playerTr->getPos();
	if (flipped) entityTr->setPos(Vector2D(playerPos.getX() + playerTr->getW() * 0.56f, playerPos.getY() + playerTr->getH() / 2.7f - entityTr->getH() * 0.57));
	else entityTr->setPos(Vector2D(playerPos.getX() + playerTr->getW() * 0.17f, playerPos.getY() + playerTr->getH() / 2.7f - entityTr->getH() * 0.62));
	adjustToCrouching();

	Vector2D mousePos(ih().getMousePos().first, ih().getMousePos().second);

	mousePos = Camera::mainCamera->PointToWorldSpace(mousePos);

	Vector2D yCenteredPos(entityTr->getPos().getX(), entityTr->getPos().getY() + entityTr->getH() * 0.37f); //Punto {0, Altura del cañón}  
	Vector2D  dir = (mousePos - yCenteredPos).normalize();

	float radianAngle = atan2(dir.getY(), dir.getX());
	float degreeAngle = (radianAngle * 180.0) / M_PI;

	float playerX = playerPos.getX() + playerTr->getW() / 2;
	float xdir = mousePos.getX() - playerX;

	if (!flipped && xdir < 0) {
		entityImg->setFlip(SDL_FLIP_VERTICAL);
		flipped = true;
	}
	else if (flipped && xdir > 0) {
		entityImg->setFlip(SDL_FLIP_NONE);
		flipped = false;
	}

	entityTr->setRot(degreeAngle);

	if (ih().getMouseButtonState(InputHandler::LEFT) && timeSinceLastShot >= fireRate
		&& bulletsInMagazine > 0 && !reloading && !playerCtrl_->isClimbingLadder()) {
		timeSinceLastShot = 0;
		Entity* bullet = entity_->getMngr()->addEntity();

		Transform* bulletTr = bullet->addComponent<Transform>(Vector2D(), 12, 6, 0);
		RigidBody* rb = bullet->addComponent<RigidBody>(dir * 10.0, false);

		float aux1 = entityTr->getW() - 8; //Distancia del cañón del arma para spawnear la bala
		float aux2 = entityTr->getPos().getY() + entityTr->getH() / 2 - yCenteredPos.getY();

		float offsetX = sin(-radianAngle) * aux2;
		float offsetY = cos(-radianAngle) * aux2;
		if (flipped) {
			offsetX = -offsetX;
			offsetY = -offsetY;
		}

		Vector2D centeredPos = { yCenteredPos.getX() - bulletTr->getW() / 2 - offsetX , entityTr->getPos().getY() + entityTr->getH() / 2 - bulletTr->getH() / 2 - offsetY}; //Punto para spawnear la bala centrada

		bulletTr->setPos(centeredPos + dir * aux1);
		bulletTr->setRot(degreeAngle);

		entity_->getMngr()->addRenderLayer<Bullets>(bullet);
		bullet->addComponent<Image>(tex_)->setRotationOrigin(8, 4);
		bullet->addComponent<Ricochet>(playerTr, nbounce, ntier);

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

void RicochetWeapon::upgradeTier(int tier) {
	if (tier == 2) {
		entity_->removeComponent<Image>();
		entity_->addComponent<Image>(&sdlutils().images().at("weapons_arms"), 3, 3, 2, 1);
		impactDamage = consts::RICOCHET_TIER2_DAMAGE;
		fireRate = consts::RICOCHET_TIER2_FIRERATE;
		nbounce++;
	}
	else if (tier == 3) {
		entity_->removeComponent<Image>();
		entity_->addComponent<Image>(&sdlutils().images().at("weapons_arms"), 3, 3, 2, 2);
		impactDamage = consts::RICOCHET_TIER3_DAMAGE;
		fireRate = consts::RICOCHET_TIER3_FIRERATE;
		nbounce++;
	}
}