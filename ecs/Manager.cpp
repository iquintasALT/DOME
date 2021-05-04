// This file is part of the course TPV2@UCM - Samir Genaim

#include "Manager.h"
#include "../components/box_collider.h"

#include <algorithm>
#include <iostream>
#include "../ecs/Entity.h"

Manager::Manager(Game* game) : game(game), sceneManager(game) {
	for (auto elem : hdlrs_)
		elem = nullptr;
}

Manager::~Manager() {
	for (auto e : entities_) {
		//if (e != getHandler<Player_hdlr>())
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
					if (e->hasComponent<BoxCollider>()) {
						//colliders.erase(e->getComponent<BoxCollider>()->getCollisionIterator()); NO SE PUEDE ACCEDER A getCollisionIterator porque tras borrar puede tener un iterador no valido
						//solucion fea temporal, buscarlo
						/*list<BoxCollider*>::iterator it = colliders.begin();
						while (it != colliders.end()) {
							if ((*it)->getEntity() == e) {
								it = colliders.erase(it);
								break;
							}
							else it++;
						}*/
						colliders.erase(e->getComponent<BoxCollider>()->getCollisionIterator());
					}
					delete e;
					return true;
				}
			}), //
		entities_.end());
}

void Manager::update() {
	for (auto i = 0u; i < entities_.size(); i++)
	{
		if (entities_[i]->active)
			entities_[i]->update();
	}
}

void Manager::render() {
	for (auto i = 0u; i < renders_.size(); i++)
		for (auto j = 0u; j < renders_[i].size(); j++)
			if (renders_[i][j] != nullptr && !renders_[i][j]->dead && renders_[i][j]->active)
				renders_[i][j]->render();
}

void Manager::removeRender(Entity* ent) {
	if (renders_.size() > ent->renderGroup && renders_[ent->renderGroup].size() > ent->renderIndex)
		renders_[ent->renderGroup][ent->renderIndex] = nullptr;
}

void Manager::AddInteractableElement(InteractableElement* ie) {
	interactableElements.push_back(ie);
}

std::list<BoxCollider*>::iterator Manager::AddCollider(BoxCollider* bc) {
	//colliders.push_back(bc);
	std::list<BoxCollider*>::iterator it = colliders.insert(colliders.end(), bc);
	return it;
}

void Manager::cycle() {
	//update();
	//refresh();
	//render();

	if (sceneManager)
		sceneManager.LoadScene();
}

void Manager::ChangeScene(GameScene* scene, SceneManager::SceneMode mode) {
	sceneManager.ChangeScene(scene, mode);
}

void Manager::addRenderNumbers(Entity* renderObj, int group) {
	renderObj->renderGroup = group;
	renderObj->renderIndex = renders_[group].size() - 1;
}