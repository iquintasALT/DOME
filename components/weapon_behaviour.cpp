#include "weapon_behaviour.h"

void WeaponBehaviour::update() {
	Vector2D playerPos = playerTr->getPos();
	entityTr->setPos(Vector2D(playerPos.getX() + playerTr->getW() * 0.5, playerPos.getY() + playerTr->getH() * 0.15));

	Vector2D mousePos(ih().getMousePos().first, ih().getMousePos().second);
	Vector2D  dir = (mousePos - entityTr->getPos()).normalize();

	float angle = (atan2(dir.getY(), dir.getX()) * 180) / M_PI;

	if (!flipped && (angle > 90 || angle < -90)) {
		entityTr->setW(-entityTr->getW());
		flipped = true;
	}
	else if (flipped && angle < 90 && angle > -90) {
		entityTr->setW(-entityTr->getW());
		flipped = false;
	}

	if (!flipped)
		entityTr->setRot(angle);
	else entityTr->setRot(angle + 180);

	if (ih().getMouseButtonState(InputHandler::LEFT)) {
		Entity* bullet = entity_->getMngr()->addEntity();

		float aux = abs(entityTr->getW() - 8);
		bullet->addComponent<Transform>(entityTr->getPos() + dir * aux, dir * 6, 16, 16, angle);
		bullet->addComponent<Image>(&sdlutils().images().at("player"), 2, 14, 0, 0);
	}
}