#include "ricochet.h"

void Ricochet::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);
}

void Ricochet::update() {
	auto& pos = tr_->getPos();
	auto& vel = tr_->getVel();
	auto height = tr_->getH();
	auto width = tr_->getW();

	if (pos.getY() < 0) {
		pos.setY(0);
		vel.setY(-vel.getY());
		n--;
	}
	else if (pos.getX() < 0) {
		pos.setX(0);
		vel.setX(-vel.getX());
		n--;
	}
	else if (pos.getY() + height > sdlutils().height()) {
		pos.setY(sdlutils().height() - height);
		vel.setY(-vel.getY());
		n--;
	}
	else if (pos.getX() + width > sdlutils().width()) {
		pos.setX(sdlutils().width() - width);
		vel.setX(-vel.getX());
		n--;
	}

	if (n == 0)
	{
		entity_->setDead(true);
	}
}