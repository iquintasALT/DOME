#include "weapon.h"
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../game/constant_variables.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../components/Image.h"
#include "../components/Transform.h"
#include "../sdlutils/SDLUtils.h"
#include "../classes/camera.h"
#include "../components/ricochet.h"
#include "../components/classic_bullet.h"
#include "../components/rigid_body.h"

#include <iostream>

Weapon::Weapon(float fR, int dam) : fireRate(fR), flipped(false), counter(0), entityImg(nullptr), damage(dam), player(nullptr),
playerTr(nullptr), entityTr(nullptr) {}
Weapon::~Weapon() {}

void Weapon::update() {
	counter++;

	Vector2D playerPos = playerTr->getPos();
	entityTr->setPos(Vector2D(playerPos.getX() + playerTr->getW() / 2, playerPos.getY() + playerTr->getH() / 2.75f - entityTr->getH() / 2));
	adjustToCrouching();

	Vector2D mousePos(ih().getMousePos().first, ih().getMousePos().second);

	mousePos = Camera::mainCamera->PointToWorldSpace(mousePos);

	Vector2D yCenteredPos(entityTr->getPos().getX(), entityTr->getPos().getY() + entityTr->getH() * 0.37f); //Punto {0, Altura del ca��n}  
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

	if (ih().getMouseButtonState(InputHandler::LEFT) && counter >= consts::FRAME_RATE / fireRate && actcharger > 0) {
		counter = 0;
		Entity* bullet = entity_->getMngr()->addEntity();

		Transform* bulletTr = bullet->addComponent<Transform>(Vector2D(), 4, 6, 0);
		RigidBody* rb = bullet->addComponent<RigidBody>(dir * 10.0, false);

		float aux1 = entityTr->getW() - 8; //Distancia del ca��n del arma para spawnear la bala
		float aux2 = entityTr->getPos().getY() + entityTr->getH() / 2 - yCenteredPos.getY();

		float offsetX = sin(-radianAngle) * aux2;
		float offsetY = cos(-radianAngle) * aux2;
		if (flipped) {
			offsetX = -offsetX;
			offsetY = -offsetY;
		}

		Vector2D centeredPos = { yCenteredPos.getX() - bulletTr->getW() / 2 - offsetX  ,entityTr->getPos().getY() + entityTr->getH() / 2 - bulletTr->getH() / 2 - offsetY }; //Punto para spawnear la bala centrada

		bulletTr->setPos(centeredPos + dir * aux1);
		bulletTr->setRot(degreeAngle);

		bullet->addComponent<Image>(&sdlutils().images().at("projectile"));

		if (actcharger == 0)
		{
			if (nbullets >= charger)
			{
				actcharger = charger;
				nbullets -= charger;
			}
			else
			{
				actcharger = nbullets;
				nbullets = 0;
			}
		}
	}

}

void Weapon::adjustToCrouching() {
	if (player->getComponent<KeyboardPlayerCtrl>() != nullptr && player->getComponent<KeyboardPlayerCtrl>()->isCrouching())
		entityTr->setPos(Vector2D(entityTr->getPos().getX(), entityTr->getPos().getY() + playerTr->getH() * 0.3f));
}

void Weapon::init()
{
	player = entity_->getMngr()->getHandler<Player_hdlr>();
	playerTr = player->getComponent<Transform>();
	entityTr = entity_->getComponent <Transform>();
	assert(entityTr != nullptr && playerTr != nullptr);

	entityImg = entity_->getComponent<Image>();
	assert(entityImg != nullptr);
	entityImg->setRotationOrigin(0, entityTr->getH() / 2);
}