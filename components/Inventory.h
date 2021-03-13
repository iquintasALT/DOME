#pragma once
#include "../ecs/Entity.h"
#include "../ecs/Component.h"
#include "../classes/Item.h"

#include <list>
class Inventory: public Component
{
public:
	Inventory(int width , int height);
	~Inventory();

	void update() override;
private:

	int width, height;
	std::list<Item*> storedItems;
};



