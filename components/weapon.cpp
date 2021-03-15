#include "weapon.h"
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../game/constant_variables.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../components/Image.h"
#include "../components/Transform.h"
#include "../sdlutils/SDLUtils.h"

void Weapon::update() {
	counter++;

	Vector2D playerPos = playerTr->getPos();
	entityTr->setPos(Vector2D(playerPos.getX() + playerTr->getW() / 2, playerPos.getY() + playerTr->getH() / 2.75f - entityTr->getH() / 2));

	Vector2D mousePos(ih().getMousePos().first, ih().getMousePos().second);


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

	if (ih().getMouseButtonState(InputHandler::LEFT) && counter >= consts::FRAME_RATE / fireRate) {
		counter = 0;
		Entity* bullet = entity_->getMngr()->addEntity();


		Transform* bulletTr = bullet->addComponent<Transform>(Vector2D(), dir * 10, 64, 64, degreeAngle);

		float aux1 = entityTr->getW() - 8; //Distancia del cañón del arma para spawnear la bala

		float aux2 = entityTr->getPos().getY() + entityTr->getH() / 2 - yCenteredPos.getY();

		float offset = ((-degreeAngle * aux2) / 90);
		if (flipped) {
			offset = ((degreeAngle * aux2) / 180);
		}

		Vector2D centeredPos = { yCenteredPos.getX() - bulletTr->getW() / 2 - offset  ,yCenteredPos.getY() - bulletTr->getH() / 2 }; //Punto para spawnear la bala centrada

		bulletTr->setPos(centeredPos + dir * aux1);

		bullet->addComponent<Image>(&sdlutils().images().at("projectile"));
	}
}

void Weapon::init()
{
	playerTr = entity_->getMngr()->getHandler<Player_hdlr>()->getComponent<Transform>();
	entityTr = entity_->getComponent <Transform>();
	assert(entityTr != nullptr && playerTr != nullptr);

	entityImg = entity_->getComponent<Image>();
	assert(entityImg != nullptr);
	entityImg->setRotationOrigin(0, entityTr->getH() / 2);
}