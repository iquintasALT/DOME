#pragma once
#include <map>
#include <iostream>
#include <vector>
#include "../components/Inventory.h"
#include "../ecs/Manager.h"
#include "../classes/player.h"
#include <vector>

#include <utility>

struct CraftableItem {
	std::string item;
	int cantidad;
	//AÑADIR MÁS INFO SI ES NECESARIA, 
};
using I = CraftableItem;

using Crafts = std::map < std::string, std::vector<I>> ; //NOMBRE / ITEMS NECESARIOS

class CraftingSystem
{
public:
	CraftingSystem(Manager* mngr);
	void CraftItem(std::string item);

private:
	Crafts crafts;
	Inventory* playerInventory;
};

