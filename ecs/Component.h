// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../utils/checkML.h"

class Entity;
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

	virtual void onEnable() {

	}
	virtual void onDisable(){

	}
	bool enabled = true;
protected:
	Entity *entity_;

	virtual void OnCollision(Entity* collider) {};
	virtual void OnTrigger(Entity* collider) {};
};

