#pragma once
#include "interactableElement.h"
#include "../components/InventoryController.h"
#include "Inventory.h"
#include "../game/constant_variables.h"
#include "../classes/player.h"
#include <string>
#include "../game/checkML.h"

class Loot :public InteractableElement
{
public:
	Loot(std::string mssg);
	void init() override;
	void Interact() override;

private:
	bool isOpen = false;

	Inventory* inventory;
	Inventory* playerInventory;
	InventoryController* inventoryController;

};

