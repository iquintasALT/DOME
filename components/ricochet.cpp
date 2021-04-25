#include "ricochet.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../components/Transform.h"
#include "../components/particleSystem.h"
#include "../utils/ray_cast.h"
#include "../components/box_collider.h"
#include "../classes/enemy.h"

Ricochet::Ricochet(Transform* player, int nrebotes, int typeOfWeapon) : tr_(nullptr), playerTr(player), n(nrebotes), tier(typeOfWeapon)
{}

Ricochet::~Ricochet() {}

void Ricochet::init() {
	tr_ = entity_->getComponent<Transform>();
	rb = entity_->getComponent<RigidBody>();
	assert(tr_ != nullptr && rb != nullptr);

	rb->bounciness = 1;
}

void Ricochet::createExplosion()
{
	auto transf = entity_->getComponent<Transform>();
	auto explosion = entity_->getMngr()->addEntity();
	Vector2D explosionOrigin = tr_->getPos() + Vector2D(tr_->getW() / 2, tr_->getH() / 2);

	Point2D arribaizq = playerTr->getPos();
	Point2D arribader = Point2D(playerTr->getPos().getX() + playerTr->getW(), arribaizq.getY());
	Point2D rayCastOrigin = Point2D(transf->getPos().getX() + (transf->getW() / 2), transf->getPos().getY() + (transf->getH() / 2));

	explosion->addComponent<Transform>(explosionOrigin, 10, 10, 0);

	auto particles = explosion->addComponent<ParticleSystem>(&sdlutils().images().at("explosion"), 1, 1, 0, 0);

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

	float x2 = playerTr->getPos().getX() + (playerTr->getW() / 2);
	float y2 = playerTr->getPos().getY() + (playerTr->getH() / 2);
	Vector2D direction = Vector2D(x2, y2);

	RayCast range = RayCast(rayCastOrigin, direction - explosionOrigin);

	//Colision enemigos
	range.rayCastToSquare(Point2D(x2, y2), arribader, arribaizq);

	if (range.hasCollision(1000))
	{
		cout << "Explosion en player";
	}
	//Colision enemigos (Cuando esten hechos xd)
	for (auto& e : entity_->getMngr()->getEntities())
	{
		if (e->hasGroup<Enemy_grp>())
		{
			x2 = e->getComponent<Transform>()->getPos().getX() + e->getComponent<Transform>()->getW() / 2;
			y2 = e->getComponent<Transform>()->getPos().getY() + e->getComponent<Transform>()->getH() / 2;
			direction = Vector2D(x2, y2);
			range.rayCastToSquare(Point2D(x2, y2), arribader, arribaizq);

			if (range.hasCollision(1000))
			{
				cout << "Explosion en player";
				//IAGO AQUI LE METES EL DAO� AL Enemigo Y EL 1000 HAY Q AJUSTARLO A LA EXPLOSION
				bool found = false;
				for (Entity* hitEnemy : hitEnemies) {
					if (hitEnemy == e) {
						found = true;
					}
				}
				if (!found) {
					static_cast<Enemy*>(e)->receiveDamage();
					hitEnemies.push_back(e);
				}
			}
		}
	}
}

void Ricochet::OnCollision(Entity* collider) {
	if (n-- == 0) {
		createExplosion();
		entity_->setDead(true);
	}
}