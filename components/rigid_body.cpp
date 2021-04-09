#include "rigid_body.h"
#include "box_collider.h"

#include "KeyboardPlayerCtrl.h"
#include <iostream>

RigidBody::RigidBody(Vector2D vel, bool gravity) : tr_(nullptr), vel_(vel),
grActive_(gravity), onFloor_(false), gravity(consts::GRAVITY), collide(true), bounciness(0) { }

RigidBody::RigidBody(Vector2D vel, Transform* tr) {
	vel_ = vel;
	tr_ = tr;
	gravity = 0;
	onFloor_ = false;
	grActive_ = false;
	collide = false;
	bounciness = 0;
}

RigidBody::~RigidBody() {};

void RigidBody::init() {
	tr_ = entity_->getComponent<Transform>();
	boxColl = entity_->getComponent<BoxCollider>();

	assert(tr_ != nullptr);
}

void RigidBody::update() {
	bool collision = false;

	bool verticalCollision = false;
	bool horizontalCollision = false;

	auto& pos = tr_->getPos();

	if (collide) {
		for (auto collider : entity_->getMngr()->getColliders()) {
			if (collider == boxColl)
				continue;

			collision = false;

			Transform* colliderTr = collider->getTransform();

			auto nextPos = tr_->getPos() + vel_;
			auto colliderPos = colliderTr->getPos();

			if (nextPos.getX() < colliderPos.getX() + colliderTr->getW() &&
				nextPos.getX() + tr_->getW() > colliderPos.getX() &&
				nextPos.getY() < colliderPos.getY() + colliderTr->getH() &&
				nextPos.getY() + tr_->getH() > colliderPos.getY())
			{
				collision = true;
			}

			if (collision) {
				if (collider->isTrigger()) {
					entity_->onTrigger(collider);
				}
				else {
					if (pos.getY() + tr_->getH() <= colliderPos.getY())
					{
						vel_.setY(vel_.getY() * -bounciness);
						onFloor_ = true;

						pos.setY(colliderPos.getY() - tr_->getH() - 1);

						verticalCollision = true;
					}
					else if (pos.getY() >= colliderPos.getY() + colliderTr->getH()) {
						vel_.setY(vel_.getY() * -bounciness);

						pos.setY(colliderPos.getY() + colliderTr->getH() + 1);

						verticalCollision = true;
					}

					else if (pos.getX() + tr_->getW() <= colliderPos.getX()) {
						vel_.setX(vel_.getX() * -bounciness);

						pos.setX(colliderPos.getX() - tr_->getW() - 1);
						horizontalCollision = true;
					}
					else if (pos.getX() >= colliderPos.getX() + colliderTr->getW()) {
						vel_.setX(vel_.getX() * -bounciness);

						pos.setX(colliderPos.getX() + colliderTr->getW() + 1);
						horizontalCollision = true;
					}

					/*if (verticalCollision)
						pos.setX(pos.getX() + vel_.getX());
					else
						pos.setY(pos.getY() + vel_.getY());*/

					entity_->onCollision(collider);
				}
			}
		}
	}
	if (!collision)
		tr_->getPos() = tr_->getPos() + vel_;
	else {
		if (!verticalCollision)
			pos.setY(pos.getY() + vel_.getY());

		if (!horizontalCollision)
			pos.setX(pos.getX() + vel_.getX());
	}
	if (grActive_) applyGravity();
}

void RigidBody::applyGravity() {
	if (!onFloor_)
		setVelY(vel_.getY() + gravity / consts::FRAME_RATE);
}

void RigidBody::reachedFloor() {
	if (vel_.getY() > consts::FALLING_DMG_SPEED) std::cout << "OUCH, CAI DESDE MUY ALTO Y YOJHAN ES FEO";
	setVelY(0);
	setOnFloor(true);
}