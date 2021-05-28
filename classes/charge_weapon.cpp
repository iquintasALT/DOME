#include "charge_weapon.h"
#include "../utils/Vector2D.h"
#include "../components/transform.h"
#include "../sdlutils/InputHandler.h"
#include "../classes/camera.h"
#include "../components/image.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../game/constant_variables.h"
#include "../components/charge.h"
#include "../utils/ray_cast.h"
#include "../game/constant_variables.h"
#include "../components/rigid_body.h"
#include "../components/weapon_animation.h"

#include "../classes/item.h"

int ChargeWeapon::bulletsInMagazine = 0;

ChargeWeapon::ChargeWeapon(int ntier, WeaponAnimation* animator) : Weapon(0.0f, ntier), tier(ntier), animator_(animator) {
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

void ChargeWeapon::update() {
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
				chargeState = not_charged;
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
