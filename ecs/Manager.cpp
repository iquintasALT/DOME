// This file is part of the course TPV2@UCM - Samir Genaim

#include "Manager.h"

#include <algorithm>

Manager::Manager() {
}

Manager::~Manager() {
	for (auto e : entities_) {
		delete e;
	}
}

void Manager::refresh() {
	// remove dead entities from the list of entities
	entities_.erase( //
		std::remove_if( //
			entities_.begin(), //
			entities_.end(), //
			[](const Entity* e) { //
				if (!e->isDead()) {
					return false;
				}
				else {
					delete e;
					return true;
				}
			}), //
		entities_.end());
}

void Manager::update() {
	for (auto i = 0u; i < entities_.size(); i++)
		entities_[i]->update();
}

void Manager::render() {
	for (auto i = 0u; i < renders_.size(); i++)
		for (auto j = 0u; j < renders_[i].size(); j++)
			renders_[i][j]->render();

}

void Manager::AddInteractableElement(InteractableElement* ie) {
	interactableElements.push_back(ie);
}

void Manager::AddCollider(BoxCollider* bc) {
	colliders.push_back(bc);
}