#pragma once
#include <list>

class Player;
class Vector2D;

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
	int weaponTiers[3];
	Vector2D position;

	class ItemSaveData {
	public:
		ItemInfo* info;
		int x, y;
		int count;
		ItemSaveData(Item* item);
		Item* createItem(Inventory* inv);
	};

	std::list<ItemSaveData*> itemsSaved;

public:
	PlayerSaveData();
	~PlayerSaveData();
	void save(Player* p);
	void load(Player* p);
	void clear();
};

