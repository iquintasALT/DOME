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
	BUILDING_PARTS, ELECTRONIC_REMAINS, METAL_PLATES, WEAPON_UPGRADE, UPGRADE_KIT, CLASSIC_AMMO, RICOCHET_AMMO, LASER_AMMO, SPACESHIP_RADAR, SPACESHIP_CABIN
	, PAINKILLER
};

class Inventory;
class ItemInfo {
private:
	ITEMS _name;
	string _description;
	string _strName;
	int _craftAmount;
	int _width;
	int _height;
	int _row;
	int _col;

	std::function<void(Entity*)> function;
	bool functionCreated;
public:
	void setAmount(int amount) { _craftAmount = amount; }
	int getAmount() { return _craftAmount; }

	static ItemInfo* bandage();
	static ItemInfo* medicalComponents();
	static ItemInfo* water();
	static ItemInfo* organicMaterial();
	static ItemInfo* mecanicalComponents();
	static ItemInfo* antidote();
	static ItemInfo* food();
	static ItemInfo* splint();
	static ItemInfo* spaceshipRockets();
	static ItemInfo* spaceshipKeyItem();
	static ItemInfo* buildingParts();
	static ItemInfo* electronicRemains();
	static ItemInfo* spaceshipRadar();
	static ItemInfo* spaceshipCabin();
	static ItemInfo* metalPlates();
	static ItemInfo* painKiller();
	static ItemInfo* weaponUpgrade();
	static ItemInfo* upgradeKit();
	static ItemInfo* laserAmmo();
	static ItemInfo* ricochetAmmo();
	static ItemInfo* classicAmmo();

	ItemInfo(ITEMS name, string strName, string description, int width, int height, int row, int col, int craftAmount = 0);
	ItemInfo(ITEMS name, string strName, string description, int width, int height, int row, int col, std::function<void(Entity*)> function, int craftAmount = 0);
	ItemInfo(ItemInfo* itemInfo);
	~ItemInfo();
	inline ITEMS name() { return _name; };
	string  strName() { return _strName; };
	inline string description() { return _description; };
	inline int width() { return _width; };
	inline int height() { return _height; };
	inline int row() { return _row; }
	inline int col() { return _col; }
	std::function<void(Entity*)> getFunc() { return function; };
	inline void execute(Entity* player) { function(player); };

	inline bool hasFunction() { return functionCreated; }
};

class Item
{
	friend class Inventory;
public:
	Item(ItemInfo* info, Manager* mnger, Inventory* inventory, int xPos = 0, int yPos = 0, int count = 0);
	Item(Item* item, Inventory* inventory);
	~Item();
	void removeImage();
	void render();
	void update();
	void setPosition(Vector2D&& pos);
	int getX() { return x; }
	int getY() { return y; }
	ItemInfo* getItemInfo();


	bool forceDelete = false;
	int count;
private:
	ItemInfo* info;
	Texture* textureNumber;
	int x, y;
	int width, height;
	Entity* image;
	Transform* transform;
	Transform* numberTr;

	Entity* countTex;
};


