#include "ricochet.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../components/Transform.h"
#include "../classes/particleSystem.h"
#include "../utils/ray_cast.h"

void Ricochet::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);
}

void Ricochet::createExplosion()
{
	auto explosion = entity_->getMngr()->addEntity();
	Vector2D explosionOrigin = tr_->getPos() + Vector2D(tr_->getW() / 2, tr_->getH() / 2);

	Point2D arribaizq = entity_->getComponent<Transform>()->getPos();
	Point2D arribader = Point2D(entity_->getComponent<Transform>()->getPos().getX() + entity_->getComponent<Transform>()->getW(), arribaizq.getY());
	Point2D squareCenter = Point2D(entity_->getComponent<Transform>()->getPos().getX() + (entity_->getComponent<Transform>()->getW() / 2), arribaizq.getY() + (entity_->getComponent<Transform>()->getH() / 2));
	
	explosion->addComponent<Transform>(explosionOrigin, Vector2D(), 10, 10, 0);

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

	float x2 = playerTr->getPos().getX() + (playerTr->getW()/2);
	float y2 = playerTr->getPos().getY() + (playerTr->getH()/2);
	Vector2D direction = Vector2D(x2,y2);

	RayCast range = RayCast(squareCenter, direction - explosionOrigin);


	//Colision enemigos
	range.rayCastToSquare(Point2D(x2, y2), arribader, arribaizq);
	if (range.hasCollision())
	{
		std::cout << range.getDistance();
	}

	//Colision enemigos (Cuando esten hechos xd)
	/*for (auto& e : entity_->getMngr()->getEnteties())
	{

	}*/
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