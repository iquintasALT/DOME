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

void ChargeWeapon::update() {
	Vector2D playerPos = playerTr->getPos();
	entityTr->setPos(Vector2D(playerPos.getX() + playerTr->getW() / 2, playerPos.getY() + playerTr->getH() / 2.75f - entityTr->getH() / 2));
	adjustToCrouching();

	Vector2D mousePos = Vector2D(ih().getMousePos().first, ih().getMousePos().second);

	mousePos = Camera::mainCamera->PointToWorldSpace(mousePos);

	Vector2D yCenteredPos(entityTr->getPos().getX(), entityTr->getPos().getY() + entityTr->getH() * 0.37f); //Punto {0, Altura del cañón}  
	Vector2D  dir = (mousePos - yCenteredPos).normalize();

	float radianAngle = atan2(dir.getY(), dir.getX());
	float degreeAngle = (radianAngle * 180) / M_PI;

	if (!flipped && (degreeAngle > 90 || degreeAngle < -90)) {
		entityImg->setFlip(SDL_FLIP_VERTICAL);
		flipped = true;
	}
	else if (flipped && degreeAngle < 90 && degreeAngle > -90) {
		entityImg->setFlip(SDL_FLIP_NONE);
		flipped = false;
	}

	entityTr->setRot(degreeAngle);

	if (ih().getMouseButtonState(InputHandler::LEFT)) {
		counter++;
	}
	else if (!ih().getMouseButtonState(InputHandler::LEFT)) {
		if (counter >= fireRate * consts::FRAME_RATE) {
			Entity* bullet = entity_->getMngr()->addEntity();


			Transform* bulletTr = bullet->addComponent<Transform>(Vector2D(), Vector2D(), 64, 64, 0);
			bulletTr->setH(1);

			//MIENTRAS NO DETECETE UNA PARED EN LA DIRECCION DEL RATÓN (ESTO ES PROVISIONAL)
			while (entityTr->getPos().getX() + bulletTr->getW() < consts::WINDOW_WIDTH) {
				bulletTr->setW(bulletTr->getW() + 1);
			}

			float aux1 = entityTr->getW() - 8; //Distancia del cañón del arma para spawnear la bala
			float aux2 = entityTr->getPos().getY() + entityTr->getH() / 2 - yCenteredPos.getY();

			float offsetX = sin(-radianAngle) * aux2;
			float offsetY = cos(-radianAngle) * aux2;
			if (flipped) {
				offsetX = -offsetX;
				offsetY = -offsetY;
			}


			Vector2D centeredPos = { yCenteredPos.getX() - offsetX  ,entityTr->getPos().getY() + entityTr->getH() / 2 - bulletTr->getH() / 2 - offsetY }; //Punto para spawnear la bala centrada


			bulletTr->setPos(centeredPos + dir * aux1);
			bulletTr->setRot(degreeAngle);

			bullet->addComponent<Image>(&sdlutils().images().at("charge"));
			bullet->getComponent<Image>()->setRotationOrigin(0, bulletTr->getH() / 2);

			bulletTr->setPos(centeredPos + dir * aux1);
			bulletTr->setRot(degreeAngle);


			bullet->addComponent<Charge>(radianAngle);

			//COMPROBAR COLISIONES CON ENEMIGOS
		}
		counter = 0;
	}
}