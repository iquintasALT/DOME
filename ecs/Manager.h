// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <initializer_list>
#include <vector>
#include <list>

#include "../utils/checkML.h"
#include "ecs.h"
#include "Entity.h"

#include "SDL_error.h"

class BoxCollider;
class InteractableElement;

class Manager {
public:
	Manager();
	virtual ~Manager();

	// entities
	Entity* addEntity() {
		Entity* e = new Entity(this);
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
	inline void setHandler(Entity* e) {
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

	inline const std::vector<BoxCollider*>& getColliders() {
		return colliders;
	}

	template<typename T>
	inline void addRenderLayer(Entity* renderObj) {
		if (renderObj->isRendering) {
			throw std::exception("Se ha intentado renderizar dos veces la misma entidad");
		}
		renderObj->isRendering = true;
		renders_[ecs::rndIdx<T>].emplace_back(renderObj);
	}

	void update();
	void render();
	void refresh();

	void AddInteractableElement(InteractableElement* ie);
	std::vector<BoxCollider*>::iterator AddCollider(BoxCollider* bc);

	inline void onNewScene() { changeScene = true; };

private:
	bool changeScene = false;
	std::vector<Entity*> entities_;
	std::array<Entity*, ecs::maxHdlr> hdlrs_;

	std::vector<InteractableElement*> interactableElements;
	std::vector<BoxCollider*> colliders;
	std::array<std::vector<Entity*>, ecs::maxRender> renders_;
};

