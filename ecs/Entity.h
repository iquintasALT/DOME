// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <algorithm>
#include <array>
#include <bitset>
#include <vector>
#include <iostream>
#include "Component.h"
#include "ecs.h"

class Manager;

class Entity {
	friend Manager;

public:

	Entity(Manager *mngr) :
			dead(true), //
			mngr_(mngr), //
			cmpArray_(), //
			groups_() //
	{
	}

	virtual ~Entity() {
		for (auto c : components_) {
			delete c;
		}
	}

	template<typename T, typename ...Ts>
	T* addComponent(Ts &&... args) {
		T *c = new T(std::forward<Ts>(args)...);
		c->setEntity(this);
		c->init();
		constexpr auto id = ecs::cmpIdx<T>;

		if (cmpArray_[id] != nullptr) {
			removeComponent<T>();
		}

		cmpArray_[id] = c;
		components_.emplace_back(c);

		return c;
	}

	template<typename T>
	void removeComponent() {
		auto id = ecs::cmpIdx<T>;
		if (cmpArray_[id] != nullptr) {
			Component *old_cmp = cmpArray_[id];
			cmpArray_[id] = nullptr;
			components_.erase( //
					std::find_if( //
							components_.begin(), //
							components_.end(), //
							[old_cmp](const Component *c) { //
								return c == old_cmp;
							}));
			delete old_cmp;
		}
	}

	template<typename T>
	inline T* getComponent() {
		auto id = ecs::cmpIdx<T>;
		return static_cast<T*>(cmpArray_[id]);
	}

	template<typename T>
	inline bool hasComponent() {
		auto id = ecs::cmpIdx<T>;
		return cmpArray_[id] != nullptr;
	}

	inline void setMngr(Manager *mngr) {
		mngr_ = mngr;
	}

	inline Manager* getMngr() {
		return mngr_;
	}

	inline bool isDead() const {
		return dead;
	}

	inline void setDead(bool state) {
		dead = state;
	}

	inline bool isActive() const {
		return active;
	}
	inline void setActive(bool _active) {
		active = _active;
	}

	template<typename T>
	inline bool hasGroup() {
		return groups_[ecs::grpIdx<T>];
	}

	template<typename T>
	inline void setGroup(bool state) {
		groups_[ecs::grpIdx<T>] = state;
	}

	inline void resetGroups() {
		groups_.reset();
	}


	void update() {
		if (!active) return;

		std::size_t n = components_.size();
		for (auto i = 0u; i < n; i++) {
			components_[i]->update();
		}
	}

	void render() {
		if (!active) return;

		std::size_t n = components_.size();
		for (auto i = 0u; i < n; i++) {
			components_[i]->render();
		}
	}

private:
	bool active;
	bool dead;
	Manager *mngr_;
	std::vector<Component*> components_;
	std::array<Component*, ecs::maxComponent> cmpArray_;
	std::bitset<ecs::maxGroup> groups_;
};

