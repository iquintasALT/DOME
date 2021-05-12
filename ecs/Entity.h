// This file is part of the course TPV2@UCM - Samir Genaim
#pragma once

#include <algorithm>
#include <array>
#include <bitset>
#include <vector>
#include <iostream>
#include "Component.h"
#include "ecs.h"
#include "../utils/checkML.h"
//#include "../ecs/Manager.cpp"

class Manager;

class Entity {
	friend Manager;

public:
	Entity() {};

	Entity(Manager* mngr) :
		dead(false), 
		active(true),
		mngr_(mngr), 
		cmpArray_(), 
		groups_(-1)
	{}

	virtual ~Entity() {
		for (auto c : components_) {
			delete c;
		}
		components_.clear();

		removeEntityRender();
	}


	template<typename T, typename ...Ts>
	T* addComponent(Ts &&... args) {
		T* c = new T(std::forward<Ts>(args)...);
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

	template<typename T, typename ActualType, typename ...Ts>
	inline ActualType* addComponent2(Ts &&...args) {
		// Create the desired component
		ActualType* c = new ActualType(std::forward<Ts>(args)...);

		// Assign entity_ pointer
		c->setEntity(this);
		// Initialize component
		c->init();

		/// Assign the component an "erroneous" id corresponding to the parent component
		/// This will disguise the child as its parent, so that the child is returned when the parent is asked for
		/// or removed when we attempt to remove the parent
		constexpr auto id = ecs::cmpIdx<T>;

		// Assure that we do not have two components with the same id on the same entity
		if (cmpArray_[id] != nullptr) {
			removeComponent<T>();
		}

		// Insert the component into the position of the component array that corresponds to the parent
		cmpArray_[id] = c;
		// Add the component to the component list as normal
		components_.emplace_back(c);
		return c;
	}

	template<typename T>
	void removeComponent() {
		auto id = ecs::cmpIdx<T>;
		if (cmpArray_[id] != nullptr) {
			Component* old_cmp = cmpArray_[id];
			cmpArray_[id] = nullptr;
			components_.erase( //
				std::find_if( //
					components_.begin(), //
					components_.end(), //
					[old_cmp](const Component* c) { //
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

	inline void setMngr(Manager* mngr) {
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

		if (active) onEnable();
		else onDisable();
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

	virtual void update() {
		for (auto i = 0u; i < components_.size(); i++) {
			if (components_[i]->enabled)
				components_[i]->update();
		}
	}

	virtual void render() {
		if (!active) return;

		for (auto i = 0u; i < components_.size(); i++) {
			if (components_[i]->enabled)
				components_[i]->render();
		}
	}

	virtual void onEnable() {
		for (auto i = 0u; i < components_.size(); i++) {
			components_[i]->onEnable();
		}
	}

	virtual void onDisable() {
		for (auto i = 0u; i < components_.size(); i++) {
			components_[i]->onDisable();
		}
	}

	void onCollision(Entity* collider) {
		for (int i = 0; i < components_.size(); i++) {
			components_[i]->OnCollision(collider);
		}
	};
	void onTrigger(Entity* collider) {
		for (int i = 0; i < components_.size(); i++) {
			components_[i]->OnTrigger(collider);
		}
	};

protected:
	Manager* mngr_;

private:
	int renderGroup;

	bool active = true, dead, isRendering = false;

	std::vector<Component*> components_;
	std::array<Component*, ecs::maxComponent> cmpArray_;
	std::bitset<ecs::maxGroup> groups_;

	void removeEntityRender();
};