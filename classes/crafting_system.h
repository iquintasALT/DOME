#pragma once
#include <map>
#include <iostream>
#include <vector>
#include "../components/inventory_controller.h"
#include "../components/loot.h"
#include "../ecs/Manager.h"
#include "../classes/player.h"
#include "../ecs/Manager.h"
#include "../utils/checkML.h"
#include <vector>
#include <iostream>

class Workshop;
#include <utility>


using Crafts = std::map < ITEMS, std::vector<ItemInfo* >>; //NOMBRE / ITEMS NECESARIOS

class CraftingSystem
{
private:
	Crafts crafts;
	Inventory* playerInventory;
	list<Item*>  itemsToDelete;
	list<Item*>  itemsToRestore;

public:
	static ItemInfo* getItemInfo(ITEMS item, int amount = 0);
	CraftingSystem(Manager* mngr);
	~CraftingSystem();
	bool CraftItem(ITEMS item, int x, int y, Workshop* ws, bool openLoot = true);
	void restoreCraft();
	Crafts* getCrafts();
};

