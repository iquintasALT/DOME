#include "loot.h"

Loot::Loot(std::string mssg) : InteractableElement(mssg), inventory(nullptr), playerInventory(nullptr), inventoryController(nullptr) {
}


void Loot::Interact() {
	isOpen = !isOpen;
	inventoryController->enabled = !isOpen;
	playerInventory->setOther((isOpen ? inventory : nullptr));
	inventoryController->OpenLoot();
}

void Loot::init() {
	InteractableElement::init();
	inventory = entity_->getComponent<Inventory>();
	inventoryController = entity_->getMngr()->getHandler<Player_hdlr>()->getComponent<InventoryController>();
	playerInventory = inventoryController->inventory;
	inventory->setOther(playerInventory);

	assert(inventory != nullptr);
	assert(inventoryController != nullptr);
	assert(playerInventory != nullptr);
}