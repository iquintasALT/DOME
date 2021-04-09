#include "loot.h"

Loot::Loot(std::string mssg) : 
	InteractableElement(mssg),
	inventory(nullptr), playerInventory(nullptr),
	inventoryController(nullptr), inventoryEntity(nullptr){
	isOpen = false;
}

void Loot::Interact() {
	isOpen = !isOpen;
	inventoryController->enabled = !isOpen;
	playerInventory->setOther((isOpen ? inventory : nullptr));

	if (isOpen) {
		playerInventory->moveInventory(new Vector2D(0, 0));
	}
	else {
		playerInventory->defaultPosition();
	}

	inventoryController->OpenLoot();
	inventoryEntity->setActive(isOpen);
}

void Loot::init() {
	InteractableElement::init();

	inventoryController = entity_->getMngr()->getHandler<Player_hdlr>()->getComponent<InventoryController>();
	playerInventory = inventoryController->inventory;
	
	assert(inventoryController != nullptr);
	assert(playerInventory != nullptr);

	inventoryEntity = entity_->getMngr()->addEntity();
	auto* tr = inventoryEntity->addComponent<Transform>(Vector2D(0, 0), 100, 100, 0);
	
	Transform* playerTransform = playerInventory->getEntity()->getComponent<Transform>();
	Point2D playerInventoryPos = playerTransform->getPos();
	float width = playerTransform->getW();

	tr->setPos(playerInventoryPos + Vector2D(width + 100, 0));

	inventoryEntity->addComponent<Image>(&sdlutils().images().at("panel"), 1, 1, 0, 0);

	inventory = inventoryEntity->addComponent<Inventory>(5, 5);
	inventory->adjustPanelSize();
	inventory->storeDefaultItems();

	inventory->setOther(playerInventory);

	inventoryEntity->setActive(false);
}