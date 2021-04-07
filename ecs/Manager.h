// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <initializer_list>
#include <vector>
#include <list>

#include "../game/checkML.h"
#include "ecs.h"
#include "Entity.h"

class InteractableElement;

class Manager {
public:
	Manager();
	virtual ~Manager();

	// entities
	Entity* addEntity() {
		Entity *e = new Entity(this);
		if (e != nullptr) {
			e->resetGroups();
			entities_.emplace_back(e);
		}
		return e;
	}

	Entity* addEntity(Entity* e) {
		if (e != nullptr) {
			e->resetGroups();
			entities_.emplace_back(e);
		}
		return e;
	}

	// handlers
	template<typename T>
	inline void setHandler(Entity *e) {
		hdlrs_[ecs::hdlrIdx<T>] = e;
	}

	template<typename T>
	inline Entity* getHandler() {
		return hdlrs_[ecs::hdlrIdx<T>];
	}

	inline const std::vector<Entity*>& getEntities() {
		return entities_;
	}

	inline const std::vector<InteractableElement*>& getInteractableElements() {
		return interactableElements;
	}
	void update();
	void render();
	void refresh();

	void AddInteractableElement(InteractableElement* ie);
private:
	std::vector<Entity*> entities_;
	std::array<Entity*, ecs::maxHdlr> hdlrs_;


	std::vector<InteractableElement*> interactableElements;
};

