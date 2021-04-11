#pragma once
#include <string>
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../components/Image.h"
#include "../components/Transform.h"
#include "../components/Inventory.h"
#include "../utils/checkML.h"

using namespace std;

enum ITEMS {
	BANDAGE, MEDICAL_COMPONENTS, WATER, ORGANIC_MATERIAL, MECANICAL_COMPONENTS, ANTIDOTE, FOOD, SPLINT, SPACESHIP_ROCKETS, SPACESHIP_KEY_ITEMS,
	BUILDING_PARTS, ELECTRONIC_REMAINS, METAL_PLATES, WEAPON_UPGRADE, UPGRADE_KIT, CLASSIC_AMMO, BACKPACK_UPGRADE, ARMOUR_UPGRADE
};

class Inventory;
class ItemInfo {
private:
	ItemInfo(ITEMS name, string description, int width, int height, Texture* texture);
	ITEMS _name;
	string _description;
	int _width;
	int _height;
	Texture* _texture;

public:
	inline ITEMS name() { return _name; };
	inline string description() { return _description; };
	inline int width() { return _width; };
	inline int height() { return _height; };
	inline Texture* texture() { return _texture; };

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
	ItemInfo* getItemInfo();

private:
	ItemInfo* info;
	int x, y;
	int width, height;
	Entity* image;
	Transform* transform;
};


