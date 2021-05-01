#pragma once
#include <string>
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../components/Image.h"
#include "../components/Transform.h"
#include "../components/Inventory.h"
#include "../utils/checkML.h"
#include <functional>
using namespace std;

enum ITEMS {
	BANDAGE, MEDICAL_COMPONENTS, WATER, ORGANIC_MATERIAL, MECANICAL_COMPONENTS, ANTIDOTE, FOOD, SPLINT, SPACESHIP_ROCKETS, SPACESHIP_KEY_ITEMS,
	BUILDING_PARTS, ELECTRONIC_REMAINS, METAL_PLATES, WEAPON_UPGRADE, UPGRADE_KIT, CLASSIC_AMMO, BACKPACK_UPGRADE, ARMOUR_UPGRADE
};

class Inventory;
class ItemInfo {
private:
	ITEMS _name;
	string _description;
	int _width;
	int _height;
	int _row;
	int _col;

	std::function<void(Entity*)> function;
public:
	ItemInfo(ITEMS name, string description, int width, int height, int row, int col, std::function<void(Entity*)> function = [](Entity*) {});
	inline ITEMS name() { return _name; };
	inline string description() { return _description; };
	inline int width() { return _width; };
	inline int height() { return _height; };
	inline int row() { return _row; }
	inline int col() { return _col; }
	inline void execute(Entity* player) { function(player); };

	static ItemInfo* bottleOfWater();
	static ItemInfo* medicine();
	static ItemInfo* food();
};

class Item
{
	friend class Inventory;
public:
	Item(ItemInfo* info, Manager* mnger, Inventory* inventory, int xPos = 0, int yPos = 0);
	~Item();
	void render();
	void update();
	void setPosition(Vector2D&& pos);
	int getX() { return x; }
	int getY() { return y; }
	ItemInfo* getItemInfo();

private:
	ItemInfo* info;
	int x, y;
	int width, height;
	Entity* image;
	Transform* transform;
};


