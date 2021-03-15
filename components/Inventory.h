#pragma once
#include "../ecs/Entity.h"
#include "../ecs/Component.h"
#include "../classes/Item.h"
#include "../components/Transform.h"

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
private:
	Vector2D itemPosition(int x, int y);
	int itemWidth, itemHeight;
	int width, height;
	Transform* transform;
	std::list<Item*> storedItems;
};



