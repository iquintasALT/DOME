#include "InventoryController.h"
#include <iostream>
#include "../classes/player.h"


InventoryController::InventoryController() {
	isOpen = true;
	inventoryPanel = nullptr;
	playerMovement = nullptr;
	playerWeapon = nullptr;

	used = false;
}

void InventoryController::init() {
	inventoryPanel = entity_->getMngr()->addEntity();
	inventoryPanel->addComponent<Transform>(Vector2D(300, 150), Vector2D(), 300, 300, 0);
	inventoryPanel->addComponent<Image>(&sdlutils().images().at("panel"), 1, 1, 0, 0);
	inventoryPanel->addComponent<Inventory>(10, 5);

	playerMovement = entity_->getComponent<KeyboardPlayerCtrl>();

	playerWeapon = static_cast<Player*>(entity_)->getCurrentWeapon()->getComponent<Weapon>();

	assert(playerMovement != nullptr);

	Use();
}

InventoryController::~InventoryController() {
	inventoryPanel->setDead(true);
}

void InventoryController::Use() {
	isOpen = !isOpen;

	inventoryPanel->setActive(isOpen);
	playerMovement->enabled = !isOpen;
	playerMovement->resetSpeed();
	playerWeapon->enabled = !isOpen;
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

	if (justPressed)
		Use();
}