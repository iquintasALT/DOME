// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../game/checkML.h"

class Entity;
class BoxCollider;

class Component {
	friend Entity;
public:
	Component() :
			entity_(nullptr) {
	}

	virtual ~Component() {
	}

	inline void setEntity(Entity *e) {
		entity_ = e;
	}

	inline Entity* getEntity() {
		return entity_;
	}

	virtual void init() {
	}

	virtual void update() {
	}

	virtual void render() {
	}

	bool enabled = true;
protected:
	Entity *entity_;

	virtual void OnCollision(BoxCollider* collider) {};
	virtual void OnTrigger(BoxCollider* collider) {};
};

