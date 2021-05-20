#include "classic_bullet.h"

#include "../ecs/Entity.h"
#include "../ecs/Manager.h"

#include "../utils/ray_cast.h"

#include "../components/Transform.h"
#include "../components/particleSystem.h"
#include "../components/box_collider.h"

#include "../classes/enemy.h"

ClassicBullet::ClassicBullet() : tr_(nullptr), rb_(nullptr) { }

ClassicBullet::~ClassicBullet() {}

void ClassicBullet::init() {
	tr_ = entity_->getComponent<Transform>();
	rb_ = entity_->getComponent<RigidBody>();
	rb_->addCollisionLayer(1);
	assert(tr_ != nullptr && rb_ != nullptr);
}

void ClassicBullet::OnCollision(Entity* other) {
	if (other->hasGroup<Enemy_grp>() ) {
		static_cast<Enemy*>(other)->receiveDamage(1);
	}
	entity_->setDead(true);
}