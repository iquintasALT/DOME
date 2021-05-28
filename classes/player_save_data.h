#pragma once
#include <list>
#include "../utils/Vector2D.h"
class Player;

class ItemInfo;
class Inventory;
class Item;
class PlayerSaveData
{
private:
	bool isSaved;

	//=====DATA=======
	float hunger;
	float tiredness;
	short int weaponTiers[3];

	class ItemSaveData {
	public:
		ItemInfo* info;
		int x, y;
		int count;
		ItemSaveData(Item* item);
		~ItemSaveData();
		Item* createItem(Inventory* inv);
	};

	std::list<ItemSaveData*> itemsSaved;

public:
	PlayerSaveData();
	~PlayerSaveData();
	void save(Player* p);
	void load(Player* p);
	void reset();
	void updateTiredness(float decTiredness);
};

