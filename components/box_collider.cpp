#include "box_collider.h"

void BoxCollider::init() {
	tr_ = entity_->getComponent<Transform>();

	assert(tr_ != nullptr);
}

bool BoxCollider::collision(Transform* trEnt_) {
	auto pos = trEnt_->getPos();
	int w = trEnt_->getW();
	int h = trEnt_->getH();

	if (tr_->getPos().getY() < pos.getY() + h) {
		pos.setY(tr_->getPos().getY() - h);
		return true;
	}
	if (tr_->getPos().getX() + tr_->getW() > pos.getX() || tr_->getPos().getX() < pos.getX() + w) {
		trEnt_->getVel().setX(0);
		return false;
	}
}