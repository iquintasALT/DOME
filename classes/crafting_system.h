#pragma once
#include <map>
#include <iostream>
#include <vector>
#include "../components/Inventory.h"
#include "../ecs/Manager.h"
#include "../classes/player.h"
#include <vector>

#include <utility>

enum ITEMS {
	BANDAGE, MEDICAL_COMPONENTS, WATER, ORGANIC_MATERIAL, MECANICAL_COMPONENTS, ANTIDOTE, FOOD, SPLINT, SPACESHIP_ROCKETS, SPACESHIP_KEY_ITEMS,
	BUILDING_PARTS, ELECTRONIC_REMAINS, METAL_PLATES, WEAPON_UPGRADE, UPGRADE_KIT, CLASSIC_AMMO, BACKPACK_UPGRADE, ARMOUR_UPGRADE
};

struct ITEMS_SPRITESHEET_INFO {
	int row;
	int col;
};

vector<ITEMS_SPRITESHEET_INFO>ITEMS_INFO = {
	//poner fila y columna de cada item
};

struct CraftableItem {
	ITEMS name;
	int cantidad;
	//AÑADIR MÁS INFO SI ES NECESARIA, 
};
using I = CraftableItem;

using Crafts = std::map < std::string, std::vector<I>>; //NOMBRE / ITEMS NECESARIOS

class CraftingSystem
{
private:
	Crafts crafts;
	Inventory* playerInventory;
public:
	CraftingSystem(Manager* mngr);
	void CraftItem(std::string item);
	Crafts* getCrafts();
};

