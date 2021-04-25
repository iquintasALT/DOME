#include "charge.h"
#include "../classes/enemy.h"

void Charge::init() {
	tr_ = entity_->getComponent<Transform>();
	rb = entity_->getComponent<RigidBody>();
	rb->addCollisionLayer(1);
	assert(tr_ != nullptr);
}

void Charge::update() {
	if (tr_->getH() < consts::CHARGEWEAPON_HEIGHT) {
		tr_->setH(tr_->getH() + 1);
		tr_->getPos().setX(tr_->getPos().getX() - sin(-angle) * 0.5f);
		tr_->getPos().setY(tr_->getPos().getY() - cos(-angle) * 0.5f);
	}
	else entity_->setDead(true);
}

void Charge::OnCollision(Entity* other)
{
	if (other->hasGroup<Enemy_grp>()) {
		bool found = false;
		for (Entity* e : hitEnemies) {
			if (e == other) {
				found = true;
			}
		}
		if (!found) {
			static_cast<Enemy*>(other)->receiveDamage();
			hitEnemies.push_back(other);
		}
	}

}
