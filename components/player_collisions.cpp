#include "player_collisions.h"

PlayerCollisions::PlayerCollisions(Manager* mngr) : mngr_(mngr), gravity_(nullptr), tr_(nullptr) {};

void PlayerCollisions::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);

	gravity_ = entity_->getComponent<GravityComponent>();
	assert(gravity_ != nullptr);
}

void PlayerCollisions::update() {
	auto& pos = tr_->getPos();
	int w = tr_->getW();
	int h = tr_->getH();

	for (auto entity : mngr_->getEnteties()) {
		if (entity->hasGroup<Wall_grp>()) {
			auto tileRend = entity->getComponent<TileRenderer>();
			assert(tileRend != nullptr);

			auto tPos = tileRend->getPos();
			int tW = tileRend->getWidth();
			int tH = tileRend->getHeight();

			if (Collisions::collides(pos, w, h, tPos, tW, tH)) {
				if (tPos.getY() < pos.getY() + h) {
					if (!gravity_->onFloor()) {
						gravity_->reachedFloor();
						tr_->setPos(Vector2D(pos.getX(), tPos.getY() - h));
					}
				}
				/*else
					tr_->setVel(Vector2D(0, tr_->getVel().getY()));*/
			}
		}
	}
}