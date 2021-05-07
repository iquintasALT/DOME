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
//	BUILDING_PARTS, ELECTRONIC_REMAINS, METAL_PLATES, WEAPON_UPGRADE, UPGRADE_KIT, CLASSIC_AMMO, SPACESHIP_RADAR, SPACESHIP_CABIN
//};


struct ITEMS_SPRITESHEET_INFO {
	int row;
	int col;
	std::string itemName;
};

const vector<ITEMS_SPRITESHEET_INFO>ITEMS_INFO = {
	{0,0,"bandage"},{0,1,"medical components"},{0,2,"water"},{1,0,"organic material"},{1,1,"mecanical components"},
	{1,2,"antidote"},{2,0,"food"},{0,0,"splint"},{0,1,"spaceship rockets"},{0,2,"spaceship key items"},{1,0,"building parts"},
	{1,1,"electronic remains"},{1,2,"metal plates"},{2,0,"weapon upgrade"},{0,0,"upgrade kit"},{0,1,"clasic ammo"},
	{2,2,"spaceship radar"}, {2,1,"spaceship cabin"}
};

struct CraftableItem {
	ITEMS name;
	int cantidad;

	int x, y, w, h, row, col;
	std::string desc;
	CraftableItem(ITEMS n, int c, int w = 0, int h = 0, int x = 0, int y = 0,int row = 0, int col = 0,string desc = "desc") : name(n), cantidad(c), x(x), y(y), w(w), h(h),col(col),row(row),desc(desc) {};
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

