#include "box_collider.h"

void BoxCollider::init() {
	tr_ = entity_->getComponent<Transform>();

	assert(tr_ != nullptr);
}