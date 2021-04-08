#include "InventoryController.h"
#include <iostream>
#include "../classes/player.h"


InventoryController::InventoryController() {
	isOpen = true;
	inventoryPanel = nullptr;
	playerMovement = nullptr;
	playerWeapon = nullptr;
	inventory = nullptr;
	used = false;
}

void InventoryController::init() {
	int width = 10, height = 5;

	inventoryPanel = entity_->getMngr()->addEntity();
	Transform* t = inventoryPanel->addComponent<Transform>(Vector2D(300, 150), Vector2D(), 300, 300, 0);
	inventoryPanel->addComponent<Image>(&sdlutils().images().at("panel"), 1, 1, 0, 0);
	inventory = inventoryPanel->addComponent<Inventory>(width, height);

	Inventory::setItemDimensions(t, width, height);
	inventory->storeDefaultItems();



	playerMovement = entity_->getComponent<KeyboardPlayerCtrl>();


	playerWeapon = static_cast<Player*>(entity_)->getCurrentWeapon()->getWeaponMovement();


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

void InventoryController::OpenLoot(){

	Use();
}

