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
#include "../game/constant_variables.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/rigid_body.h"
#include <iostream>

Weapon::Weapon(float fR, int dam, float dispersion) : dispersion(dispersion), fireRate(fR), flipped(false), ctrl(nullptr), counter(0), entityImg(nullptr), damage(dam), player(nullptr),
playerTr(nullptr), entityTr(nullptr)
{
	charger = 30; //Pasar por referencia cuando este
	actcharger = 30;
	nbullets = 50;
	tcharger = actcharger;
	recharge = 0;
	recharging = false;
}
Weapon::~Weapon() {}

void Weapon::update() {
	counter++;

	if (ctrl->isStairs()) entityImg->enabled = false;
	else entityImg->enabled = true;

	Vector2D playerPos = playerTr->getPos();
	if (flipped) entityTr->setPos(Vector2D(playerPos.getX() + playerTr->getW() / 1.25, playerPos.getY() + playerTr->getH() / 2.75f - entityTr->getH() / 2));
	else entityTr->setPos(Vector2D(playerPos.getX() + playerTr->getW() / 4, playerPos.getY() + playerTr->getH() / 2.75f - entityTr->getH() / 2));
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

	if (ih().getMouseButtonState(InputHandler::LEFT) && counter >= consts::FRAME_RATE / fireRate
		&& actcharger > 0 && !recharging && !ctrl->isStairs()) {
		counter = 0;

		float maxDispersion = dispersion; //Add here the dispersions
		if (!playerRb->onFloor()) {
			maxDispersion += 60;
		}
		float x = dir.getX();
		float y = dir.getY();
		float rotation = 0;
		if (maxDispersion != 0)
			rotation = sdlutils().rand().nextInt(-maxDispersion, maxDispersion) * M_PI / 180.0;

		dir.setX(x * cos(rotation) - y * sin(rotation));
		dir.setY(x * sin(rotation) + y * cos(rotation));

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

		entity_->getMngr()->addRenderLayer<Bullets>(bullet);
		bullet->addComponent<Image>(&sdlutils().images().at("projectile"));
		bullet->addComponent<ClassicBullet>();
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

void Weapon::recharger()
{
	std::cout << nbullets << " ";
	if (nbullets > 0 && actcharger < charger && !recharging)
	{
		recharging = true;
		nbullets -= tcharger - actcharger;
		if (nbullets >= charger - actcharger)
		{
			actcharger = charger;
		}
		else
		{
			actcharger += nbullets;
			nbullets = 0;
		}
		tcharger = actcharger;
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
	ctrl = player->getComponent<KeyboardPlayerCtrl>();
	assert(entityTr != nullptr && playerTr != nullptr && ctrl != nullptr);

	entityImg = entity_->getComponent<Image>();
	assert(entityImg != nullptr);
	entityImg->setRotationOrigin(0, entityTr->getH() / 2);

	playerRb = player->getComponent<RigidBody>();
	assert(playerRb != nullptr);
}

void Weapon::upgradeTier(int tier) {
	if (tier == 2) {
		entity_->removeComponent<Image>();
		entity_->addComponent<Image>(&sdlutils().images().at("weapons_arms"), 3, 3, 0, 1);
		damage = consts::WEAPON_TIER2_DAMAGE;
		fireRate = consts::WEAPON_TIER2_FIRERATE;
	}
	else if (tier == 3) {
		entity_->removeComponent<Image>();
		entity_->addComponent<Image>(&sdlutils().images().at("weapons_arms"), 3, 3, 0, 2);
		damage = consts::WEAPON_TIER3_DAMAGE;
		fireRate = consts::WEAPON_TIER3_FIRERATE;
	}
}