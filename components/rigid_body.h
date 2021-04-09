#pragma once

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../utils/Vector2D.h"
#include "../utils/checkML.h"
#include "../game/constant_variables.h"

#include "Transform.h"

class RigidBody : public Component {
	friend BoxCollider;
private:
	Transform* tr_;
	BoxCollider* boxColl;

	Vector2D vel_;

	float gravity;
	bool onFloor_, grActive_;

	bool collide;
	bool collisions[consts::COLLISION_LAYERS];
public:
	RigidBody(Vector2D vel = Vector2D(), bool gravity = true);
	RigidBody(Vector2D vel, Transform* tr);

	virtual ~RigidBody();

	virtual void init() override;

	inline Vector2D& getVel() { return vel_; }

	inline void setVel(Vector2D vel) { vel_ = vel; }

	inline void setVelX(float x) { vel_.setX(x); }

	inline void setVelY(float y) { vel_.setY(y); }

	virtual void applyGravity();

	void reachedFloor();

	inline bool onFloor() { return onFloor_; };

	inline void setOnFloor(const bool floor) { onFloor_ = floor; };

	inline void update() override;

	inline void addCollisionLayer(int l) { collisions[l] = true; };
	inline void removeCollisionLayer(int l) { collisions[l] = false; };
	inline bool checkCollisionLayer(int l) { return collisions[l]; };

	float bounciness;
};
