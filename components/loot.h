#pragma once
#include "interactableElement.h"
#include "Inventory.h"
#include "../classes/player.h"
#include <string>
class Loot :public InteractableElement
{
public:
	Loot(std::string mssg);
	void init() override;
	void Interact() override;

private:
	Inventory* inventory;
	Inventory* playerInventory;
};

