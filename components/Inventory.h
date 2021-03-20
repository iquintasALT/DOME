#pragma once
#include "../ecs/Entity.h"
#include "../ecs/Component.h"
#include "../classes/Item.h"
#include "../components/Transform.h"
#include "../game/constant_variables.h"
#include "../game/checkML.h"

#include <list>
class Inventory: public Component
{
	friend class Item;
public:
	Inventory(int width, int height);
	Inventory(int width , int height, Inventory* player);
	~Inventory();

	void init() override;
	void update() override;
	void render() override;

	void storeItem(Item* item);
	void moveItem(Item* item, int x, int y);
	void removeItem(Item* item);
	void storeDefaultItems();

	static void setItemDimensions(Transform* transform, int width, int height);
	void adjustPanelSize();
private:
	const float timeToHold = 0.08f; //seconds
	float timer = 0;

	Inventory* player;

	Vector2D itemPosition(int x, int y);
	static int itemWidth, itemHeight;
	int width, height;
	Transform* transform;

	std::list<Item*> storedItems;

	std::vector<std::vector<Item*>> grid;

	Item* findItemInSlot(int x, int y);

	bool avaliableSpace(int x, int y, int w, int h, Item* item);

	bool justPressed;
	Item* selectedItem;
	Item* selectedItem_;
};



