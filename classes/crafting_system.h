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

struct ITEMS_SPRITESHEET_INFO {
	int row;
	int col;
	std::string itemName;
};

const vector<ITEMS_SPRITESHEET_INFO> ITEMS_INFO = {
	{0,2,"bandage"},
	{0,1,"medical components"},
	{4,0,"water"},
	{1,2,"organic material"},
	{4,1,"mechanical components"},
	{1,0,"antidote"},
	{2,0,"food"},
	{5,1,"splint"},
	{6,0,"spaceship rockets"},
	{4,2,"spaceship key items"},
	{7,0,"building parts"},
	{5,0,"electronic remains"},
	{7,1,"metal plates"},
	{7,2,"weapon upgrade"},
	{6,2,"upgrade kit"},
	{2,1,"clasic ammo"},
	{3,1,"ricochet ammo"},
	{3,0,"laser ammo"},
	{5,2,"spaceship radar"},
	{6,1,"spaceship cabin"}, 
	{0,0,"painkiller"}
};


struct CraftableItem {
	ITEMS name;
	int cantidad;

	int x, y, w, h, row, col;
	std::string desc;
	std::function<void(Entity*)> function;

	CraftableItem(ITEMS n, int c, int w = 0, int h = 0, int x = 0, int y = 0, int row = 0, int col = 0, string desc = "desc", 
		std::function<void(Entity*)>f = [](Entity* player) {}) 
		: name(n), cantidad(c), x(x), y(y), w(w), h(h), col(col), row(row), desc(desc) {};
	//A�ADIR M�S INFO SI ES NECESARIA, 
	CraftableItem(int x_, int y_, ItemInfo item) {
		name = item._name;
		desc = item._description;
		cantidad = 0;
		x = x_; y = y_;
		w = item._width; h = item._height;
		row = item._row; col = item._col;
		function = item.function;
	}
};
using I = CraftableItem;

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
	bool CraftItem(ITEMS item, int x, int y, Workshop* ws, bool openLoot = true);
	void restoreCraft();
	Crafts* getCrafts();
};