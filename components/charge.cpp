#include "charge.h"

void Charge::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);
}

void Charge::update() {
	if (tr_->getH() < consts::CHARGEWEAPON_HEIGHT) {
		tr_->setH(tr_->getH() + 1);
	}
	else entity_->setDead(true);
}