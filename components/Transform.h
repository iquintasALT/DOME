// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include "../game/checkML.h"

class Transform : public Component {
public:
	Transform() :
		pos_(), vel_(), width_(), height_(), rotation_() {
	}

	Transform(Vector2D pos, Vector2D vel, float width, float height,
		float rotation) :
		pos_(pos), //
		vel_(vel), //
		width_(width), //
		height_(height), //
		rotation_(rotation)
	{
	}

	virtual ~Transform() {
	}

	Vector2D& getPos() {
		return pos_;
	}

	Vector2D& getVel() {
		return vel_;
	}

	float getH() const {
		return height_;
	}

	void setH(float height) {
		height_ = height;
	}

	float getW() const {
		return width_;
	}

	void setW(float width) {
		width_ = width;
	}

	float getRot() const {
		return rotation_;
	}

	void setRot(float rot) {
		rotation_ = rot;
	}

	void setVel(Vector2D vel) {
		vel_ = vel;
	}

	void setVelX(float x) {
		vel_.setX(x);
	}

	void setVelY(float y) {
		vel_.setY(y);
	}

	void setPos(Vector2D pos) {
		pos_ = pos;
	}

	void update() override {
		pos_ = pos_ + vel_;
	}

private:
	Vector2D pos_;
	Vector2D vel_;
	float width_;
	float height_;
	float rotation_;
};

