// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <initializer_list>
#include <vector>
#include <list>

#include "../utils/checkML.h"
#include "ecs.h"
#include "Entity.h"

#include "SDL_error.h"
#include "../classes/scene_manager.h"

class BoxCollider;
class InteractableElement;


class Game;
class Manager {
public:
	Manager() = delete;
	Manager(Game* game);
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

	inline const std::list<BoxCollider*>& getColliders() {
		return colliders;
	}

	template<typename T>
	inline void addRenderLayer(Entity* renderObj) {
		if (renderObj->isRendering) {
			throw std::exception("Se ha intentado renderizar dos veces la misma entidad");
		}
		renderObj->isRendering = true;
		renderObj->renderGroup = ecs::rndIdx<T>;
		renders_[renderObj->renderGroup].emplace_back(renderObj);
	}

	void update();
	void render();
	void refresh();
	void cycle();

	void AddInteractableElement(InteractableElement* ie);
	std::list<BoxCollider*>::iterator AddCollider(BoxCollider* bc);

	inline void onNewScene() { changeScene = true; };

	/// <param name="mode">
	/// ADDITIVE: A new Scene is added to the pile
	/// SINGLE: The whole pile is removed and then this scene is pushed
	/// OVERRIDE: The last scene is overwritten and changed by the new one
	/// </param>
	void ChangeScene(GameScene* scene, SceneManager::SceneMode mode);

	inline Game* getGame() { return game; }

private:
	bool changeScene = false;
	std::vector<Entity*> entities_;
	std::array<Entity*, ecs::maxHdlr> hdlrs_;

	std::vector<InteractableElement*> interactableElements;
	std::list<BoxCollider*> colliders;
	std::array<std::list<Entity*>, ecs::maxRender> renders_;

	SceneManager sceneManager;
	Game* game;
};


