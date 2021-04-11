#pragma once
#include <map>
#include <iostream>
#include <vector>
#include "../components/Inventory.h"
#include "../ecs/Manager.h"
#include "../classes/player.h"
#include "../utils/checkML.h"
#include <vector>

#include <utility>

//enum ITEMS {
//	BANDAGE, MEDICAL_COMPONENTS, WATER, ORGANIC_MATERIAL, MECANICAL_COMPONENTS, ANTIDOTE, FOOD, SPLINT, SPACESHIP_ROCKETS, SPACESHIP_KEY_ITEMS,
//	BUILDING_PARTS, ELECTRONIC_REMAINS, METAL_PLATES, WEAPON_UPGRADE, UPGRADE_KIT, CLASSIC_AMMO, BACKPACK_UPGRADE, ARMOUR_UPGRADE
//};

struct ITEMS_SPRITESHEET_INFO {
	int row;
	int col;
	std::string itemName;
};

const vector<ITEMS_SPRITESHEET_INFO>ITEMS_INFO = {
	{0,0,"bandage"},{0,1,"medical components"},{0,2,"water"},{1,0,"organic material"},{1,1,"mecanical components"},
	{1,2,"antidote"},{2,0,"food"},{0,0,"splint"},{0,1,"spaceship rockets"},{0,2,"spaceship key items"},{1,0,"building parts"},
	{1,1,"electronic remains"},{1,2,"metal plates"},{2,0,"weapon upgrade"},{0,0,"upgrade kit"},{0,1,"clasic ammo"},{0,2,"backpack upgrade"},
	{1,0,"armour upgrade"}
};

struct CraftableItem {
	ITEMS name;
	int cantidad;
	//AÑADIR MÁS INFO SI ES NECESARIA, 
};
using I = CraftableItem;

using Crafts = std::map < ITEMS, std::vector<I>>; //NOMBRE / ITEMS NECESARIOS

class CraftingSystem
{
private:
	Crafts crafts;
	Inventory* playerInventory;
public:
	CraftingSystem(Manager* mngr);
	void CraftItem(ITEMS item);
	Crafts* getCrafts();
};

