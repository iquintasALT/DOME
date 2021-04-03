#pragma once

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../utils/Vector2D.h"
#include "../game/checkML.h"

#include "Transform.h"

class RigidBody : public Component {
private:
	Transform* tr_;

	Vector2D vel_;
	float rotation_;

public:
	RigidBody();

	RigidBody(Vector2D vel, float rotation = 0);

	virtual ~RigidBody();

	virtual void init() override;

	inline float getRot() const { return rotation_; }

	inline void setRot(float rot) { rotation_ = rot; }

	inline Vector2D& getVel() { return vel_; }

	inline void setVel(Vector2D vel) { vel_ = vel; }

	inline void setVelX(float x) { vel_.setX(x); }

	inline void setVelY(float y) { vel_.setY(y); }

	inline void update() override;
};
