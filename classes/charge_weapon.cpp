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

#include "../classes/Item.h"

ChargeWeapon::ChargeWeapon(float fR, int dam) : Weapon(fR, dam) {};

void ChargeWeapon::update() {
	if (ctrl->isStairs()) entityImg->enabled = false;
	else entityImg->enabled = true;

	Vector2D playerPos = playerTr->getPos();
	if (flipped) entityTr->setPos(Vector2D(playerPos.getX() + playerTr->getW() * 0.56f, playerPos.getY() + playerTr->getH() / 2.7f - entityTr->getH() * 0.57));
	else entityTr->setPos(Vector2D(playerPos.getX() + playerTr->getW() * 0.17f, playerPos.getY() + playerTr->getH() / 2.7f - entityTr->getH() * 0.62));
	adjustToCrouching();

	Vector2D mousePos = Vector2D(ih().getMousePos().first, ih().getMousePos().second);

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

	if (currentCharger != nullptr && ih().getMouseButtonState(InputHandler::LEFT) && !recharging && !ctrl->isStairs()) {
		shootTime += consts::DELTA_TIME;
	}
	else if (!ih().getMouseButtonState(InputHandler::LEFT)) {
		if (shootTime >= fireRate && currentCharger->count > 0) {
			Entity* bullet = entity_->getMngr()->addEntity();

			Transform* bulletTr = bullet->addComponent<Transform>(Vector2D(), 64, 64, 0);
			bulletTr->setH(1);
			

			float aux1 = entityTr->getW() - 8; //Distancia del cañón del arma para spawnear la bala
			float aux2 = entityTr->getPos().getY() + entityTr->getH() / 2 - yCenteredPos.getY();

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


			Vector2D centeredPos = { yCenteredPos.getX() - offsetX  ,entityTr->getPos().getY() + entityTr->getH() / 2 - bulletTr->getH() / 2 - offsetY }; //Punto para spawnear la bala centrada


			bulletTr->setPos(centeredPos + dir * aux1);
			bulletTr->setRot(degreeAngle);

			entity_->getMngr()->addRenderLayer<Bullets>(bullet);
			bullet->addComponent<Image>(&sdlutils().images().at("charge"));
			bullet->getComponent<Image>()->setRotationOrigin(0, bulletTr->getH() / 2);

			bullet->addComponent<Charge>(radianAngle, raycast);

			//COMPROBAR COLISIONES CON ENEMIGOS
			currentCharger->count--;
			if (currentCharger->count == 0)
			{
				recharge();
			}
			delete raycast;
		}
		shootTime = 0;
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

void ChargeWeapon::upgradeTier(int tier) {
	if (tier == 2) {
		entity_->removeComponent<Image>();
		entity_->addComponent<Image>(&sdlutils().images().at("weapons_arms"), 3, 3, 1, 1);
		damage = consts::CHARGE_TIER2_DAMAGE;
		fireRate = consts::CHARGE_TIER2_FIRERATE;
	}
	else if (tier == 3) {
		entity_->removeComponent<Image>();
		entity_->addComponent<Image>(&sdlutils().images().at("weapons_arms"), 3, 3, 1, 2);
		damage = consts::CHARGE_TIER3_DAMAGE;
		fireRate = consts::CHARGE_TIER3_FIRERATE;
	}
}
