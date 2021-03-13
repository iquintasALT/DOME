#pragma once

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"

class InventoryController: public Component
{
public :
	InventoryController();
	~InventoryController();

	void Use();
protected:
	bool isOpen = false;
	Entity* inventoryPanel;
};

