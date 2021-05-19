#include "charge_weapon.h"
#include "../utils/Vector2D.h"
#include "../components/Transform.h"
#include "../sdlutils/InputHandler.h"
#include "../classes/camera.h"
#include "../components/Image.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../game/constant_variables.h"
#include "../components/charge.h"
#include "../utils/ray_cast.h"
#include "../game/constant_variables.h"
#include "../components/rigid_body.h"
#include "../components/weapon_animation.h"

#include "../classes/Item.h"

int ChargeWeapon::bulletsInMagazine = 0;

ChargeWeapon::ChargeWeapon(float fR, int dam, int ntier, WeaponAnimation* animator) : Weapon(fR, dam, 0.0f, ntier), tier(ntier), animator_(animator) {
	type = LASER;
};

Entity* ChargeWeapon::createBullet(const Vector2D& direction) {
	Entity* bullet = entity_->getMngr()->addEntity();
	Transform* bulletTr = bullet->addComponent<Transform>(Vector2D(), 4, 6, 0);

	bulletTr->setH(1);
	float squareX = consts::WINDOW_WIDTH * consts::WINDOW_WIDTH;
	Vector2D yCenteredPos(tr_->getPos().getX(), tr_->getPos().getY() + tr_->getH() * 0.37f); //Punto {0, Altura del cañon}  
	RayCast* raycast = new RayCast(yCenteredPos, direction);
	float aux1 = tr_->getW() - 8; //Distancia del cañón del arma para spawnear la bala
	float width = raycast->distanceToGroup<Wall_grp>(entity_->getMngr()) - aux1;
	if (width + aux1 != -1)
		bulletTr->setW(width);
	else bulletTr->setW(sqrt(squareX + squareX));

	bullet->addComponent<Image>(&sdlutils().images().at("charge"));
	bullet->getComponent<Image>()->setRotationOrigin(0, bulletTr->getH() / 2);
	bullet->addComponent<Charge>(atan2(direction.getY(), direction.getX()), raycast);
	entity_->getMngr()->addRenderLayer<Bullets>(bullet);
	return bullet;
}

void ChargeWeapon::update() {/*
	if (playerCtrl_->isClimbingLadder()) image_->enabled = false;
	else image_->enabled = true;

	Vector2D playerPos = playerTr_->getPos();
	if (flipped) tr_->setPos(Vector2D(playerPos.getX() + playerTr_->getW() * 0.56f, playerPos.getY() + playerTr_->getH() / 2.7f - tr_->getH() * 0.57));
	else tr_->setPos(Vector2D(playerPos.getX() + playerTr_->getW() * 0.17f, playerPos.getY() + playerTr_->getH() / 2.7f - tr_->getH() * 0.62));
	adjustToCrouching();

	Vector2D mousePos = Vector2D(ih().getMousePos().first, ih().getMousePos().second);

	mousePos = Camera::mainCamera->PointToWorldSpace(mousePos);

	Vector2D yCenteredPos(tr_->getPos().getX(), tr_->getPos().getY() + tr_->getH() * 0.37f); //Punto {0, Altura del cañón}  
	Vector2D  dir = (mousePos - yCenteredPos).normalize();

	float radianAngle = atan2(dir.getY(), dir.getX());
	float degreeAngle = (radianAngle * 180.0) / M_PI;

	float playerX = playerPos.getX() + playerTr_->getW() / 2;
	float xdir = mousePos.getX() - playerX;

	if (!flipped && xdir < 0) {
		image_->setFlip(SDL_FLIP_VERTICAL);
		flipped = true;
	}
	else if (flipped && xdir > 0) {
		image_->setFlip(SDL_FLIP_NONE);
		flipped = false;
	}

	tr_->setRot(degreeAngle);

	if (ih().getMouseButtonState(InputHandler::LEFT) && !reloading && !playerCtrl_->isClimbingLadder()) {
		timeSinceLastShot += consts::DELTA_TIME;
	}
	else if (!ih().getMouseButtonState(InputHandler::LEFT)) {
		if (timeSinceLastShot >= fireRate && bulletsInMagazine > 0) {
			Entity* bullet = entity_->getMngr()->addEntity();

			Transform* bulletTr = bullet->addComponent<Transform>(Vector2D(), 64, 64, 0);
			bulletTr->setH(1);
			

			float aux1 = tr_->getW() - 8; //Distancia del cañón del arma para spawnear la bala
			float aux2 = tr_->getPos().getY() + tr_->getH() / 2 - yCenteredPos.getY();

			Transform auxMousePos = Transform(mousePos, 1, 1, 0);
			RayCast* raycast = new RayCast(yCenteredPos, dir);
			float width = raycast->distanceToGroup<Wall_grp>(entity_->getMngr()) - aux1;

			//	std::cout << actcharger << std::endl;
			//	std::cout << nbullets << std::endl;

			float squareX = consts::WINDOW_WIDTH * consts::WINDOW_WIDTH;

			if (width + aux1 != -1)
				bulletTr->setW(width);
			else bulletTr->setW(sqrt(squareX + squareX));


			float offsetX = sin(-radianAngle) * aux2;
			float offsetY = cos(-radianAngle) * aux2;
			if (flipped) {
				offsetX = -offsetX;
				offsetY = -offsetY;
			}


			Vector2D centeredPos = { yCenteredPos.getX() - offsetX  ,tr_->getPos().getY() + tr_->getH() / 2 - bulletTr->getH() / 2 - offsetY }; //Punto para spawnear la bala centrada


			bulletTr->setPos(centeredPos + dir * aux1);
			bulletTr->setRot(degreeAngle);

			entity_->getMngr()->addRenderLayer<Bullets>(bullet);
			bullet->addComponent<Image>(&sdlutils().images().at("charge"));
			bullet->getComponent<Image>()->setRotationOrigin(0, bulletTr->getH() / 2);

			bullet->addComponent<Charge>(radianAngle, raycast);

			soundManager().playSFX("laser");

			//COMPROBAR COLISIONES CON ENEMIGOS
			bulletsInMagazine--;
			if (bulletsInMagazine <= 0)
			{
				reload();
			}
			delete raycast;
		}
		timeSinceLastShot = 0;
	}

	if (reloading)
	{
		reloadTime += consts::DELTA_TIME;
	}
	if (reloadTime > 2.0) //Tiempo de recarga en segundos
	{
		reloadTime = 0;
		reloading = false;
	}*/
	if (!playerCtrl_->isClimbingLadder())
	{
		if (!image_->enabled) image_->enabled = true;
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
		/*else if (ih().getMouseButtonState(InputHandler::LEFT) && timeSinceLastShot >= fireRate &&
			bulletsInMagazine > 0 && !reloading)
			shoot(rotation);*/

		/*else if (ih().getMouseButtonState(InputHandler::LEFT) && bulletsInMagazine > 0 && chargeState == not_charged) {
			timeSinceLastShot += consts::DELTA_TIME;
			animator_->setAnimation(9 + tier);
			chargeState = winding_up;
		}
		else if (timeSinceLastShot >= fireRate){
			shoot(rotation);
			animator_->setAnimation(6 + tier);
			chargeState = winding_up;
		}
		// If mouse is released early, reset charge
		else if (!ih().getMouseButtonState(InputHandler::LEFT) && chargeState == winding_up) {
			timeSinceLastShot = 0;
			animator_->setAnimation(6 + tier)
		}*/
		else
		switch (chargeState)
		{
		case not_charged:
			if (ih().getMouseButtonState(InputHandler::LEFT) && bulletsInMagazine > 0) {
				timeSinceLastShot += consts::DELTA_TIME;
				animator_->setAnimation(9 + tier);
				chargeState = winding_up;
			}
			break;
		case winding_up:
			if (ih().getMouseButtonState(InputHandler::LEFT))
			{
				timeSinceLastShot += consts::DELTA_TIME;
				if (timeSinceLastShot >= fireRate) {
					animator_->setAnimation(12 + tier);
					chargeState = charged;
				}
			}
			else // If mouse is released early, reset charge
			{
				timeSinceLastShot = 0;
				animator_->setAnimation(6 + tier);
			}
			break;
		case charged:
			if (!ih().getMouseButtonState(InputHandler::LEFT)) {
				shoot(rotation);
				animator_->setAnimation(6 + tier);
				chargeState = not_charged;
			}
			break;
		}
	}
	else
	image_->enabled = false;
}

void ChargeWeapon::upgradeCurrentWeapon(int tier) {
	if (tier == 1) {
		impactDamage = consts::CHARGE_TIER2_DAMAGE;
		fireRate = consts::CHARGE_TIER2_TIMETOCHARGE;
	}
	else if (tier == 2) {
		impactDamage = consts::CHARGE_TIER3_DAMAGE;
		fireRate = consts::CHARGE_TIER3_TIMETOCHARGE;
	}
}
