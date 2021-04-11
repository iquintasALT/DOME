#include "classic_bullet.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../components/Transform.h"
#include "../components/particleSystem.h"
#include "../utils/ray_cast.h"
#include "../components/box_collider.h"

ClassicBullet::ClassicBullet(Transform* player, int typeOfWeapon) : tr_(nullptr), playerTr(player), tier(typeOfWeapon)
{
}

ClassicBullet::~ClassicBullet() {}

void ClassicBullet::init() {
	tr_ = entity_->getComponent<Transform>();
	rb = entity_->getComponent<RigidBody>();
	assert(tr_ != nullptr && rb != nullptr);
}

void ClassicBullet::createExplosion()
{
	auto transf = entity_->getComponent<Transform>();

	Vector2D explosionOrigin = tr_->getPos() + Vector2D(tr_->getW() / 2, tr_->getH() / 2);

	Point2D arribaizq = playerTr->getPos();
	Point2D arribader = Point2D(playerTr->getPos().getX() + playerTr->getW(), arribaizq.getY());
	Point2D rayCastOrigin = Point2D(transf->getPos().getX() + (transf->getW() / 2), transf->getPos().getY() + (transf->getH() / 2));



	float x2 = playerTr->getPos().getX() + (playerTr->getW() / 2);
	float y2 = playerTr->getPos().getY() + (playerTr->getH() / 2);
	Vector2D direction = Vector2D(x2, y2);

	RayCast range = RayCast(rayCastOrigin, direction - explosionOrigin);

	//Colision enemigos
	range.rayCastToSquare(Point2D(x2, y2), arribader, arribaizq);
	//if (range.hasCollision())
	//{
	std::cout << "\nRango Raycast " << range.getDistance();
	//}

	//Colision enemigos (Cuando esten hechos xd)
	/*for (auto& e : entity_->getMngr()->getEnteties())
	{

	}*/
}

void ClassicBullet::OnCollision(BoxCollider* collider) {
	createExplosion();
	entity_->setDead(true);
}