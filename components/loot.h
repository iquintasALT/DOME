#pragma once
#include "interactable_element.h"
#include "inventory.h"
#include "../components/inventory_controller.h"
#include "../game/constant_variables.h"
#include "../classes/player.h"
#include <string>
#include "../utils/checkML.h"

using namespace std;

class Manager;
class Loot :public InteractableElement
{
protected:
	bool isOpen;
	bool isTutorial;
	Inventory* inventory;
private:
	static const float margin;

	Entity* inventoryEntity;
	Inventory* playerInventory;
	InventoryController* inventoryController;
	Transform* playerTransform;
	Transform* inventoryTransform;

	int invenWidth, invenHeight;
public:
	Loot(string mssg, int width, int height);
	~Loot();
	void init() override;
	void Interact() override;
	inline Inventory* getInventory() { return inventory; }
	inline Entity* getInventoryEntity() { return inventoryEntity; };


};

