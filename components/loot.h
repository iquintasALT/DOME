#pragma once
#include "interactableElement.h"
#include "../components/InventoryController.h"
#include "Inventory.h"
#include "../game/constant_variables.h"
#include "../classes/player.h"
#include <string>
#include "../utils/checkML.h"

using namespace std;

class Manager;
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

	int invenWidth, invenHeight;
public:
	Loot(string mssg, int width, int height);
	void init() override;
	void Interact() override;
	inline Inventory* getInventory() { return inventory; }


};

