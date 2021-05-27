// This file is part of the course TPV2@UCM - Samir Genaim

#include "Manager.h"
#include "../components/box_collider.h"

#include <algorithm>
#include <iostream>
#include "../ecs/Entity.h"
#include "../game/Game.h"
#include "../components/Inventory.h"
#include "../components/weapon.h"

Manager::Manager(Game* game) : game(game), sceneManager(game) {
	for (auto elem : hdlrs_)
		elem = nullptr;
}

Manager::~Manager() {
	for (auto e : entities_) {
		if (e == getHandler<Player_hdlr>())
			getGame()->playerSavedData->save(static_cast<Player*>(e));
		delete e;
	}
	entities_.clear();
}

void Manager::refresh() {
	// remove dead entities from the list of entities
	entities_.erase( //
		std::remove_if( //
			entities_.begin(), //
			entities_.end(), //
			[&](Entity* e) { //
				if (!e->isDead()) {
					return false;
				}
				else {
					if (e->hasComponent<BoxCollider>()) // eliminacion del collider guardado
						colliders.erase(e->getComponent<BoxCollider>()->getCollisionIterator());
					if (e->renderGroup > -1) // eliminacion de la capa de renderizado
						renders_[e->renderGroup].remove(e);
					delete e;
					return true;
				}
			}), //
		entities_.end());
}

void Manager::update() {
	for (auto i = 0u; i < entities_.size(); i++)
		if (entities_[i]->active)
			entities_[i]->update();
}

void Manager::render() {
	for (auto i = 0u; i < renders_.size(); i++)
		for (auto renderIt : renders_[i])
			if (!renderIt->dead && renderIt->active)
				renderIt->render();
}

void Manager::AddInteractableElement(InteractableElement* ie) {
	interactableElements.push_back(ie);
}

std::list<BoxCollider*>::iterator Manager::AddCollider(BoxCollider* bc) {
	std::list<BoxCollider*>::iterator it = colliders.insert(colliders.end(), bc);
	return it;
}

void Manager::cycle() {
	if (sceneManager)
		sceneManager.LoadScene();
}

void Manager::ChangeScene(GameScene* scene, SceneManager::SceneMode mode) {
	sceneManager.ChangeScene(scene, mode);
}