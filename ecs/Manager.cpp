// This file is part of the course TPV2@UCM - Samir Genaim

#include "Manager.h"
#include "../components/box_collider.h"

#include <algorithm>

Manager::Manager() {
}

Manager::~Manager() {
	for (auto e : entities_) {
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
			[&]( Entity* e) { //
				if (!e->isDead()) {
					return false;
				}
				else {
					if (e->hasComponent<BoxCollider>()) {
						//colliders.erase(e->getComponent<BoxCollider>()->getCollisionIterator()); NO SE PUEDE ACCEDER A getCollisionIterator porque tras borrar puede tener un iterador no valido
						//solucion fea temporal, buscarlo
						vector<BoxCollider*>::iterator it = colliders.begin();
						while (it != colliders.end()) {
							if ((*it)->getEntity() == e) {
								it = colliders.erase(it);
								break;
							}
							else it++;
						}
					}
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
		for (auto j = 0u; j < renders_[i].size(); j++)
			if (!renders_[i][j]->dead && renders_[i][j]->active)
				renders_[i][j]->render();
}

void Manager::AddInteractableElement(InteractableElement* ie) {
	interactableElements.push_back(ie);
}

std::vector<BoxCollider*>::iterator Manager::AddCollider(BoxCollider* bc) {
	//colliders.push_back(bc);
	std::vector<BoxCollider*>::iterator it = colliders.end();
	it = colliders.insert(it, bc);
	return it;
}