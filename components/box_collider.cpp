#include "box_collider.h"

#include "rigid_body.h"

void BoxCollider::init() {
	tr_ = entity_->getComponent<Transform>();

	entity_->getMngr()->AddCollider(this);
	assert(tr_ != nullptr);
}

bool BoxCollider::collision(Transform* trEnt_, RigidBody* rb_) {
	auto pos = trEnt_->getPos();
	int w = trEnt_->getW();
	int h = trEnt_->getH();

	bool below = false;

	if (tr_->getPos().getY() < pos.getY() + h) {
		pos.setY(tr_->getPos().getY() - h);
		below = true;
	}
	if (tr_->getPos().getX() + tr_->getW() < pos.getX() || tr_->getPos().getX() > pos.getX() + w) {
		rb_->getVel().setX(0);
	}

	return below;
}