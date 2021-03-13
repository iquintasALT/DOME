#include "InventoryController.h"
#include <iostream>

InventoryController::InventoryController() {
	isOpen = true;
	inventoryPanel = nullptr;
	playerMovement = nullptr;
	playerWeapon = nullptr;

	used = false;
}

void InventoryController::init() {
	inventoryPanel = entity_->getMngr()->addEntity();
	playerMovement = entity_->getComponent<KeyboardPlayerCtrl>();
	//playerWeapon = entity_->getComponent<WeaponBehaviour>();

	assert(playerMovement != nullptr);

	//assert(playerWeapon != nullptr);

	Use();
}

InventoryController::~InventoryController() {
	inventoryPanel->setDead(false);
}

void InventoryController::Use() {
	isOpen = !isOpen;

	inventoryPanel->setActive(isOpen);
	playerMovement->enabled = !isOpen;
	playerMovement->resetSpeed();
	//playerWeapon->enabled = !isOpen;
}

void InventoryController::update() {
	bool justPressed = false;
	if (used) {
		if (ih().isKeyUp(SDLK_TAB)) {
			used = false;
		}
	}
	else {
		if (ih().isKeyDown(SDLK_TAB)) {
			justPressed = true;
			used = true;
		}
	}

	if (!justPressed) return;

	std::cout << "Hey" << std::endl;
	Use();
}