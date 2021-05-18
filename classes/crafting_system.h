#pragma once
#include <map>
#include <iostream>
#include <vector>
#include "../components/InventoryController.h"
#include "../components/loot.h"
#include "../ecs/Manager.h"
#include "../classes/player.h"
#include "../ecs/Manager.h"
#include "../utils/checkML.h"
#include <vector>
#include <iostream>

class Workshop;
#include <utility>

//enum ITEMS {
//	BANDAGE, MEDICAL_COMPONENTS, WATER, ORGANIC_MATERIAL, MECANICAL_COMPONENTS, ANTIDOTE, FOOD, SPLINT, SPACESHIP_ROCKETS, SPACESHIP_KEY_ITEMS,
//	BUILDING_PARTS, ELECTRONIC_REMAINS, METAL_PLATES, WEAPON_UPGRADE, UPGRADE_KIT, CLASSIC_AMMO, RICOCHET_AMMO, LASER_AMMO, SPACESHIP_RADAR, SPACESHIP_CABIN
//};


struct ITEMS_SPRITESHEET_INFO {
	int row;
	int col;
	std::string itemName;
};

const vector<ITEMS_SPRITESHEET_INFO>ITEMS_INFO = {
	{0,2,"bandage"},{0,1,"medical components"},{4,0,"water"},{1,2,"organic material"},{4,1,"mecanical components"},
	{1,0,"antidote"},{2,0,"food"},{5,1,"splint"},{6,0,"spaceship rockets"},{4,2,"spaceship key items"},{7,0,"building parts"},
	{5,0,"electronic remains"},{7,1,"metal plates"},{2,0,"weapon upgrade"},{6,2,"upgrade kit"},{2,1,"clasic ammo"},{3,1,"ricochet ammo"},{3,0,"laser ammo"},
	{5,2,"spaceship radar"}, {6,1,"spaceship cabin"}
};

struct CraftableItem {
	ITEMS name;
	int cantidad;

	int x, y, w, h, row, col;
	std::string desc;
	CraftableItem(ITEMS n, int c, int w = 0, int h = 0, int x = 0, int y = 0, int row = 0, int col = 0, string desc = "desc") : name(n), cantidad(c), x(x), y(y), w(w), h(h), col(col), row(row), desc(desc) {};
	//AÑADIR MÁS INFO SI ES NECESARIA, 
};
using I = CraftableItem;

using Crafts = std::map < ITEMS, std::vector<I>>; //NOMBRE / ITEMS NECESARIOS

class CraftingSystem
{
private:
	Crafts crafts;
	Inventory* playerInventory;
	list<Item*>  itemsToDelete;
public:
	CraftingSystem(Manager* mngr);
	bool CraftItem(ITEMS item, int x, int y, Workshop* ws, bool openLoot = true);
	void FinishCraft();
	Crafts* getCrafts();
};

