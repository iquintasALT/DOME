#include "player_collisions.h"
#include "GravityComponent.h"

PlayerCollisions::PlayerCollisions(Manager* mngr, GravityComponent* gr) : mngr_(mngr), gravity_(gr) {};

bool PlayerCollisions::collisions(Vector2D& newPos, int const w, int const h, Vector2D& vel) {
	bool hasCollide = false;

	for (auto entity : mngr_->getEnteties()) {
		if (entity->hasGroup<Wall_grp>()) {
			auto tileRend = entity->getComponent<TileRenderer>();
			assert(tileRend != nullptr);

			auto tPos = tileRend->getPos();
			int tW = tileRend->getWidth();
			int tH = tileRend->getHeight();

			if (Collisions::collides(newPos, w, h, tPos, tW, tH)) {
				if (tPos.getY() < newPos.getY() + h) {
					gravity_->reachedFloor();
				}
				if ((tPos.getX() + tW > newPos.getX() || tPos.getX() < newPos.getX() + w) && tPos.getY() >= newPos.getY() + h) {
					vel.setX(0);
				}
				hasCollide = true;
			}
		}
	}
	
	return hasCollide;
}
void PlayerCollisions::init() {

}