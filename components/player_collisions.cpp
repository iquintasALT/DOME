#include "player_collisions.h"
#include "GravityComponent.h"
#include "box_collider.h"
#include "Transform.h"

PlayerCollisions::PlayerCollisions() : gravity_(nullptr){};

void PlayerCollisions::update() {
	for (auto entity : entity_->getMngr()->getEnteties()) {
		if (entity->hasGroup<Wall_grp>()) {
			auto tileRend = entity->getComponent<Transform>();
			assert(tileRend != nullptr);

			auto tPos = tileRend->getPos();
			int tW = tileRend->getW();
			int tH = tileRend->getH();

			auto tr_ = entity_->getComponent<Transform>();

			if (Collisions::collides(tr_->getPos(), tr_->getW(), tr_->getH(), tPos, tW, tH)) {
				auto collider = entity->getComponent<BoxCollider>();
				if (collider->collision(tr_)) gravity_->reachedFloor();
			}
		}
	}
}

void PlayerCollisions::init() {
	gravity_ = entity_->getComponent<GravityComponent>();

	assert(gravity_ != nullptr);
}