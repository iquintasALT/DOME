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

void ClassicBullet::OnCollision(BoxCollider* collider) {
	entity_->setDead(true);
}