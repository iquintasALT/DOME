#pragma once
#include "../ecs/Entity.h"
#include "../ecs/Component.h"
#include "../classes/Item.h"
#include "../components/Transform.h"
#include "../game/constant_variables.h"
#include "../utils/checkML.h"
#include "../classes/inventoryDropdown.h"


#include <list>
#include <string>
#include <functional>
class TextWithBackground;
class Game;

class Inventory : public Component
{
	friend class Item;
public:
	Inventory(int width, int height);
	Inventory(int width, int height, Inventory* player);
	~Inventory();

	void init() override;
	void update() override;
	void render() override;

	list<Item*>& getItems();

	void storeItem(Item* item);
	void moveItem(Item* item, int x, int y);
	void removeItem(Item* item);
	void storeDefaultItems();

	static void setItemDimensions(Transform* transform, int width, int height);
	void adjustPanelSize();

	inline void setOther(Inventory* o) { other = o; };
	void defaultPosition();

	void moveInventory(Point2D pos);

	void onEnable() override;
	void onDisable() override;
private:
	Point2D originalPos;
	const float timeToHold = 0.08f; //seconds
	float timer = 0;

	Inventory* other;

	Vector2D itemPosition(int x, int y);
	Vector2D itemPosition(int x, int y, Transform* transform);

	static int itemWidth, itemHeight;
	int width, height;
	Transform* transform;

	std::list<Item*> storedItems;

	std::vector<std::vector<Item*>> grid;

	Item* findItemInSlot(int x, int y);

	bool avaliableSpace(int x, int y, Item* item);

	bool justPressed;
	Item* selectedItem;
	Item* selectedItem_;
	Item* itemClickedInDropdown;

	bool insideSquare(int mouseX, int mouseY, Transform* rect);
	bool insideSquare(int mouseX, int mouseY);

	bool dropDownActive;

	inventoryDropdown* dropDown;
	Entity* toolTips;
	Transform* toolTipsTr;
	TextWithBackground* toolTipsText;
	bool showToolTip;
};
