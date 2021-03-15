#pragma once
#include "../ecs/Entity.h"
#include "../ecs/Component.h"
#include "../classes/Item.h"
#include "../components/Transform.h"

#include <list>
class Inventory: public Component
{
public:
	Inventory(int width , int height);
	~Inventory();

	void init() override;
	void update() override;
private:

	int width, height;
	Transform* transform;
	std::list<Item*> storedItems;
};



