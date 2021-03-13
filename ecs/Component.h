// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

class Entity;

class Component {
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

};

