#pragma once
#include "interactableElement.h"
#include "../components/InventoryController.h"
#include "Inventory.h"
#include "../game/constant_variables.h"
#include "../classes/player.h"
#include <string>
#include "../utils/checkML.h"

using namespace std;

class Loot :public InteractableElement
{
private:
	static const float margin;
	bool isOpen;

	Entity* inventoryEntity;
	Inventory* inventory;
	Inventory* playerInventory;
	InventoryController* inventoryController;
	Transform* playerTransform;
	Transform* inventoryTransform;
public:
	Loot(string mssg);
	void init() override;
	void Interact() override;
};

