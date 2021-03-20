#include "loot.h"

Loot::Loot(std::string mssg) : InteractableElement(mssg), inventory(nullptr), playerInventory(nullptr) {

}


void Loot::Interact() {
	std::cout << "Interact with cosa";
}

void Loot::init() {
	InteractableElement::init();
	inventory = entity_->getComponent<Inventory>();
	playerInventory = entity_->getMngr()->getHandler<Player_hdlr>()->getComponent<Inventory>();
	assert(inventory != nullptr);
	//assert(playerInventory != nullptr);
}