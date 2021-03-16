#pragma once
#include "../ecs/Entity.h"
#include "../ecs/Component.h"
#include "../classes/Item.h"
#include "../components/Transform.h"
#include "../game/constant_variables.h"

#include <list>
class Inventory: public Component
{
	friend class Item;
public:
	Inventory(int width , int height);
	~Inventory();

	void init() override;
	void update() override;
	void render() override;

	void storeItem(Item* item);
	void moveItem(Item* item, int x, int y);
private:
	const float timeToHold = 0.08f; //seconds
	float timer = 0;

	Vector2D itemPosition(int x, int y);
	int itemWidth, itemHeight;
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



