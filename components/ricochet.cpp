#include "ricochet.h"

#include <list>
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../components/transform.h"
#include "../components/particle_system.h"
#include "../utils/ray_cast.h"
#include "../components/box_collider.h"
#include "../classes/enemy.h"
#include "../utils/ray_cast.h"
#include "../sdlutils/SoundManager.h"

Ricochet::Ricochet(Transform* player, int nrebotes, int typeOfWeapon) : tr_(nullptr), playerTr(player),
n(nrebotes), tier(typeOfWeapon) {}

Ricochet::~Ricochet() {}

void Ricochet::init() {
	tr_ = entity_->getComponent<Transform>();
	rb = entity_->getComponent<RigidBody>();
	rb->addCollisionLayer(1);
	assert(tr_ != nullptr && rb != nullptr);

	rb->bounciness = 1;
}

void Ricochet::createExplosion()
{
	auto transf = entity_->getComponent<Transform>();

	auto explosion = entity_->getMngr()->addEntity();

	entity_->getMngr()->addRenderLayer<Player>(explosion);

	Vector2D explosionOrigin = tr_->getPos() + Vector2D(tr_->getW() / 2, tr_->getH() / 2);


	explosion->addComponent<Transform>(explosionOrigin, 10, 10, 0);

	auto particles = explosion->addComponent<ParticleSystem>(&sdlutils().images().at("explosion"), 1, 1, 0, 0);

	particles->distanceToOrigin = 0;
	particles->dir = Vector2D(-1, 0);
	particles->angleDispersion = 360;
	particles->burst = true;
	particles->rateOverTime = 0;
	particles->burstCount = 100;
	particles->lifeTime = 0.1f;
	particles->speed = 7;
	particles->gravity = false;
	particles->emitting = false;
	particles->particleScale = 2;

	particles->destroyAfterBurst = true;
	particles->burstDuration = 0.02f;
	particles->burstRepeat = 8;

	soundManager().playSFX("explosion");
	Point2D rayCastOrigin = Point2D(transf->getPos().getX() + (transf->getW() / 2), transf->getPos().getY() + (transf->getH() / 2));


	float x2 = playerTr->getPos().getX() + (playerTr->getW() / 2);
	float y2 = playerTr->getPos().getY() + (playerTr->getH() / 2);
	Vector2D direction = Vector2D(x2, y2);

	hitEnemies(rayCastOrigin);
}

void Ricochet::hitEnemies(Point2D raycastOrigin)
{
	std::list<Entity*> collided = RayCast::allCollisionsInRadius<Enemy_grp>(entity_->getMngr(), raycastOrigin, 55);
	for (Entity* hit_entity : collided) {
		static_cast<Enemy*>(hit_entity)->receiveDamage(2);
	}
}

void Ricochet::OnCollision(Entity* other) {
	if (n-- == 0 || other->hasGroup<Enemy_grp>()) {
		createExplosion();
		entity_->setDead(true);
	}
	else //Choca con pared
	{
		soundManager().playSFX("bounce");
	}
}
