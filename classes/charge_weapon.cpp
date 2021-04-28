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

ChargeWeapon::ChargeWeapon(float fR, int dam) : Weapon(fR, dam) {};

void ChargeWeapon::update() {
	Vector2D playerPos = playerTr->getPos();
	if(flipped) entityTr->setPos(Vector2D(playerPos.getX() + playerTr->getW() / 1.5, playerPos.getY() + playerTr->getH() / 2.75f - entityTr->getH() / 2));
	else entityTr->setPos(Vector2D(playerPos.getX() + playerTr->getW() / 3.25, playerPos.getY() + playerTr->getH() / 2.75f - entityTr->getH() / 2));
	adjustToCrouching();

	Vector2D mousePos = Vector2D(ih().getMousePos().first, ih().getMousePos().second);

	mousePos = Camera::mainCamera->PointToWorldSpace(mousePos);

	Vector2D yCenteredPos(entityTr->getPos().getX(), entityTr->getPos().getY() + entityTr->getH() * 0.37f); //Punto {0, Altura del cañón}  
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

	if (ih().getMouseButtonState(InputHandler::LEFT) && !recharging) {
		counter++;
	}
	else if (!ih().getMouseButtonState(InputHandler::LEFT)) {
		if (counter >= fireRate * consts::FRAME_RATE && actcharger > 0) {
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
			actcharger--;
			if (actcharger == 0 && nbullets > 0)
			{
				recharging = true;
				nbullets -= tcharger;
				if (nbullets >= charger)
				{
					actcharger = charger;
				}
				else
				{
					actcharger = nbullets;
					nbullets = 0;
				}
				tcharger = actcharger;
			}
			delete raycast;
		}
		counter = 0;
	}

	if (recharging)
	{
		recharge += consts::DELTA_TIME;
	}
	if (recharge > 2.0) //Tiempo de recarga en segundos
	{
		recharge = 0;
		recharging = false;
	}
}
