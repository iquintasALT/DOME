#include "rigid_body.h"
#include "box_collider.h"

#include "KeyboardPlayerCtrl.h"
#include <iostream>

RigidBody::RigidBody(Vector2D vel, float rotation, bool gravity) : tr_(nullptr), vel_(vel), rotation_(rotation),
grActive_(gravity), onFloor_(false), gravity(consts::GRAVITY), collide(true) { }

RigidBody::RigidBody(Vector2D vel, Transform* tr) {
	vel_ = vel;
	tr_ = tr;
	rotation_ = 0;
	gravity = 0;
	onFloor_ = false;
	grActive_ = false;
	collide = false;
}

RigidBody::~RigidBody() {};

void RigidBody::init() {
	tr_ = entity_->getComponent<Transform>();

	assert(tr_ != nullptr);
}

void RigidBody::update() {
	if (collide) {
		for (auto collider : entity_->getMngr()->getColliders()) {

			bool collision = false;

			Transform* colliderTr = collider->getTransform();

			auto pos = tr_->getPos();
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
						vel_.setY(0);
						onFloor_ = true;
					}
					else if (pos.getY() >= colliderPos.getY() + colliderTr->getH()) {
						vel_.setY(0);
					}

					if (pos.getX() + tr_->getW() <= colliderPos.getX()) {
						vel_.setX(0);
					}
					else if (pos.getX() >= colliderPos.getX() + colliderTr->getW()) {
						vel_.setX(0);
					}

					entity_->onCollision(collider);
				}
			}
		}
	}
	tr_->getPos() = tr_->getPos() + vel_;
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