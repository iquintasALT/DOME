#include "ricochet.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../components/Transform.h"
#include "../classes/particleSystem.h"

void Ricochet::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);
}

void Ricochet::createExplosion()
{
	auto explosion = entity_->getMngr()->addEntity();
	Vector2D pos = tr_->getPos() + Vector2D(tr_->getW() / 2, tr_->getH() / 2);
	explosion->addComponent<Transform>(pos, Vector2D(), 10, 10, 0);

	auto particles = explosion->addComponent<ParticleSystem>(&sdlutils().images().at("dust"), 1, 1, 0, 0);

	particles->distanceToOrigin = 0;
	particles->dir = Vector2D(-1, 0);
	particles->angleDispersion = 180;
	particles->burst = true;
	particles->rateOverTime = 0;
	particles->burstCount = 100;
	particles->lifeTime = 0.1f;
	particles->speed = 7;
	particles->gravity = false;
	particles->emitting = false;
	particles->particleScale = 2;

	particles->burstDuration = 0.02f;
	particles->burstRepeat = 8;


	/*particles->gravity = 0;
	particles->lifeTime = 100;
	particles->rateOverTime = 0;
	particles->speed = 0;
	particles->burst = true;
	particles->destroyAfterBurst = false;
	particles->burstRepeat = 1;*/
}

void Ricochet::update() {
	auto& pos = tr_->getPos();
	auto& vel = tr_->getVel();
	auto height = tr_->getH();
	auto width = tr_->getW();

	if (pos.getY() < 0) {
		pos.setY(0);
		vel.setY(-vel.getY());
		n--;
	}
	else if (pos.getX() < 0) {
		pos.setX(0);
		vel.setX(-vel.getX());
		n--;
	}
	else if (pos.getY() + height > sdlutils().height()) {
		pos.setY(sdlutils().height() - height);
		vel.setY(-vel.getY());
		n--;
	}
	else if (pos.getX() + width > sdlutils().width()) {
		pos.setX(sdlutils().width() - width);
		vel.setX(-vel.getX());
		n--;
	}

	if (n == 0)
	{
		createExplosion();
		entity_->setDead(true);
	}
}