#include "loot.h"

const float Loot::margin = 100;

Loot::Loot(std::string mssg) : 
	InteractableElement(mssg),
	inventory(nullptr), playerInventory(nullptr),
	inventoryController(nullptr), inventoryEntity(nullptr){
	isOpen = false;
	playerTransform = nullptr;
}

void Loot::Interact() {
	isOpen = !isOpen;
	inventoryController->enabled = !isOpen;
	playerInventory->setOther((isOpen ? inventory : nullptr));

	if (isOpen) {
		float maxWidth = playerTransform->getW() + inventoryTransform->getW() + margin;
		float x = (sdlutils().width() - maxWidth) / 2;

		playerInventory->moveInventory(new Vector2D(x, playerTransform->getPos().getY()));
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
	inventoryTransform = inventoryEntity->addComponent<Transform>(Vector2D(0, 0), 100, 100, 0);
	
	playerTransform = playerInventory->getEntity()->getComponent<Transform>();
	
	float maxWidth = playerTransform->getW() + inventoryTransform->getW() + margin;
	float x = (sdlutils().width() - maxWidth) / 2 + playerTransform->getW();


	inventoryTransform->setPos(new Vector2D(x, playerTransform->getPos().getY()));

	inventoryEntity->addComponent<Image>(&sdlutils().images().at("panel"), 1, 1, 0, 0);

	inventory = inventoryEntity->addComponent<Inventory>(5, 5);
	inventory->adjustPanelSize();
	inventory->storeDefaultItems();

	inventory->setOther(playerInventory);

	inventoryEntity->setActive(false);
}