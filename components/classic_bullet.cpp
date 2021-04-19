#include "classic_bullet.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../components/Transform.h"
#include "../components/particleSystem.h"
#include "../utils/ray_cast.h"
#include "../components/box_collider.h"


#include "../components/enemy_component.h"


ClassicBullet::ClassicBullet(Transform* player, int typeOfWeapon) : tr_(nullptr), playerTr(player), tier(typeOfWeapon)
{
}

ClassicBullet::~ClassicBullet() {}

void ClassicBullet::init() {
	tr_ = entity_->getComponent<Transform>();
	rb = entity_->getComponent<RigidBody>();
	rb->addCollisionLayer(1);
	assert(tr_ != nullptr && rb != nullptr);
}

void ClassicBullet::OnCollision(Entity* other) {
	EnemyComponent* a = other->getComponent<EnemyComponent>();
	if (other->hasGroup<Enemy_grp>() ) {
		other->setDead(true);
	}
	std::cout << "hola";
	entity_->setDead(true);
}