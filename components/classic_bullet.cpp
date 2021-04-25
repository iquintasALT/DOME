#include "classic_bullet.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../components/Transform.h"
#include "../components/particleSystem.h"
#include "../utils/ray_cast.h"
#include "../components/box_collider.h"


#include "../components/enemy_component.h"


ClassicBullet::ClassicBullet() : tr_(nullptr), rb_(nullptr) { }

ClassicBullet::~ClassicBullet() {}

void ClassicBullet::init() {
	tr_ = entity_->getComponent<Transform>();
	rb_ = entity_->getComponent<RigidBody>();
	rb_->addCollisionLayer(1);
	assert(tr_ != nullptr && rb_ != nullptr);
}

void ClassicBullet::OnCollision(Entity* other) {
	EnemyComponent* a = other->getComponent<EnemyComponent>();
	if (other->hasGroup<Enemy_grp>() ) {
		other->setDead(true);
	}
	std::cout << "hola";
	entity_->setDead(true);
}