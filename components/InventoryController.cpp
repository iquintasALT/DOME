#include "InventoryController.h"
#include <iostream>

InventoryController::InventoryController() {
	isOpen = true;
	inventoryPanel = nullptr;
	playerMovement = nullptr;
	playerWeapon = nullptr;
}

void InventoryController::init() {
	inventoryPanel = entity_->getMngr()->addEntity();
	return;
	playerMovement = entity_->getComponent<KeyboardPlayerCtrl>();
	playerWeapon = entity_->getComponent<WeaponBehaviour>();

	assert(playerMovement != nullptr && playerWeapon != nullptr);

	Use();
}

InventoryController::~InventoryController() {
	delete inventoryPanel;
}

void InventoryController::Use() {
	isOpen = !isOpen;

	inventoryPanel->setActive(isOpen);
	playerMovement->enabled = !isOpen;
	playerWeapon->enabled = !isOpen;
}

void InventoryController::update() {
	if (ih().isKeyDown(SDLK_TAB)) {
		Use();
		std::cout << "HEY";
	}
}