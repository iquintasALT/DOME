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

void RicochetWeapon::update() {
	counter++;

	Vector2D playerPos = playerTr->getPos();
	entityTr->setPos(Vector2D(playerPos.getX() + playerTr->getW() / 2, playerPos.getY() + playerTr->getH() / 2.75f - entityTr->getH() / 2));
	adjustToCrouching();

	Vector2D mousePos(ih().getMousePos().first, ih().getMousePos().second);

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

	if (ih().getMouseButtonState(InputHandler::LEFT) && counter >= consts::FRAME_RATE / fireRate) {
		counter = 0;
		Entity* bullet = entity_->getMngr()->addEntity();

		Transform* bulletTr = bullet->addComponent<Transform>(Vector2D(), 4, 6, 0);
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

		bullet->addComponent<Image>(&sdlutils().images().at("projectile"));
		bullet->addComponent<Ricochet>(playerTr, nbounce, ntier);
	}
}