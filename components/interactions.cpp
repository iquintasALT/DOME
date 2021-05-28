#include "interactions.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../components/interactable_element.h"
void Interactions::init() {
	manager = entity_->getMngr();
	transform = entity_->getComponent<Transform>();
}

void Interactions::update() {
	InteractableElement* IE = nullptr;
	for (auto ie : manager->getInteractableElements()) {
		if (ie->CheckCollision(transform->getPos(), transform->getW(), transform->getH())) {
			IE = ie;
		}
	}

	if (IE != nullptr)
		if (keystates[SDL_SCANCODE_E]) {
			if (!justPressed) {
				IE->Interact();
				justPressed = true;
			}
		}
		else {
			if (justPressed) {

				justPressed = false;
			}
		}
}