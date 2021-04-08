#include "rigid_body.h"
#include "box_collider.h"

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

			auto& pos = tr_->getPos();
			auto& colliderPos = colliderTr->getPos();

			if (pos.getX() < colliderPos.getX() + colliderTr->getW() &&
				pos.getX() + tr_->getW() > colliderPos.getX() &&
				pos.getY() < colliderPos.getY() + colliderTr->getH() &&
				pos.getY() + tr_->getH() > colliderPos.getY())
			{
				collision = true;
			}

			if (collision)
				std::cout << "Hola parece que las colisiones funcionan" << std::endl;

			if (collider->isTrigger()) {

			}
			else {

			}
		}
	}


	tr_->getPos() = tr_->getPos() + vel_;
	if (grActive_) applyGravity();
}

void RigidBody::applyGravity() {
	if (!onFloor_)
		setVelY(vel_.getY() + gravity / consts::FRAME_RATE);

	//if (entityTr->getPos().getY() > 600) entityTr->setVelY(0);
}

void RigidBody::reachedFloor() {
	if (vel_.getY() > consts::FALLING_DMG_SPEED) std::cout << "OUCH, CAI DESDE MUY ALTO Y YOJHAN ES FEO";
	setVelY(0);
	setOnFloor(true);
}