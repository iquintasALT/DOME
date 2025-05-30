#include "inventory_controller.h"
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
	float trwidth = 450;
	float trheight = 450;
	float xpos = (sdlutils().width() - trwidth) / 2;
	float ypos = (sdlutils().height() - trheight) / 2;
	Transform* t = inventoryPanel->addComponent<Transform>(Vector2D(xpos, ypos), trwidth, trheight, 0);
	inventoryPanel->addComponent<Image>(&sdlutils().images().at("storage"), 2, 2, 0, 0, true);
	entity_->getMngr()->addRenderLayer<Interface>(inventoryPanel);


	playerWeapon = static_cast<Player*>(entity_)->getWeapon();

	inventory = inventoryPanel->addComponent<Inventory>(width, height, playerWeapon);

	Inventory::setItemDimensions(t, width, height);
	if(Inventory::firstInitialization)
		inventory->storeDefaultItems();

	playerMovement = entity_->getComponent<KeyboardPlayerCtrl>();

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
	playerWeapon->getCurrentWeapon()->enabled = !isOpen;
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

void InventoryController::OpenLoot(bool state) {
	if (isOpen != state)
		Use();
}
