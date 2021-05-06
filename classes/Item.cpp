#include "Item.h"

ItemInfo::ItemInfo(ITEMS name, string description, int width, int height, int row, int col, std::function<void(Entity* p)> f) :
	_name(name), _description(description), _width(width), _height(height), _row(row), _col(col), function(f) {};

ItemInfo::ItemInfo(ItemInfo* item) {
	_name = item->_name;
	_description = item->_description;
	_width = item->_width;
	_height = item->_height;
	_row = item->_row;
	_col = item->_col;
	function = item->function;
}

ItemInfo* ItemInfo::bottleOfWater()
{
	auto f = [](Entity* player) {
		std::cout << "has usado la botella de agua";
	};

	return new ItemInfo(WATER, "Scarse item, use it carefully", 1, 2, 4, 0, f);
}
ItemInfo* ItemInfo::medicine()
{
	return new ItemInfo(ANTIDOTE, "Mmmmmm", 2, 2, 0, 1);
}

ItemInfo* ItemInfo::food()
{
	return new ItemInfo(FOOD, "I dont know what im doing", 1, 1, 1, 2);
}

ItemInfo* ItemInfo::defaultAmmo()
{
	return new ItemInfo(CLASSIC_AMMO, "This is the classic ammo item", 1, 1, 1, 2);
}

//&sdlutils().images().at("items")

Item::Item(ItemInfo* itemInformation, Manager* mngr, Inventory* inventory, int xPos, int yPos) :
	info(itemInformation), x(xPos), y(yPos) {

	width = info->width();
	height = info->height();
	image = mngr->addEntity();
	mngr->addRenderLayer<Item>(image);
	transform = image->addComponent<Transform>(inventory->itemPosition(x, y),
		Inventory::itemWidth * width, Inventory::itemHeight * height, 0);
	image->addComponent<Image>(&sdlutils().images().at("items"), 8, 3, info->row(), info->col(), true);
	image->setActive(false);
}

Item::Item(Item* item, Inventory* inventory) {
	info = item->info;
	width = item->width;
	height = item->height;
	x = item->x;
	y = item->y;
	if (inventory != nullptr) {
		Manager* mngr = inventory->entity_->getMngr();
		image = mngr->addEntity();
		mngr->addRenderLayer<Item>(image);
		transform = image->addComponent<Transform>(inventory->itemPosition(x, y),
			Inventory::itemWidth * width, Inventory::itemHeight * height, 0);
		image->addComponent<Image>(&sdlutils().images().at("items"), 6, 3, info->row(), info->col(), true);
		image->setActive(false);
	}
	else {
		image = nullptr;
		transform = nullptr;
	}
}

Item::~Item() {
	delete info;
	if (image != nullptr)
		image->setDead(true);
}

void Item::render() {
	image->setActive(true);
	image->render();
	image->setActive(false);
}

void Item::update() {
	image->setActive(true);
	image->update();
	image->setActive(false);
}

void Item::setPosition(Vector2D&& pos) {
	transform->setPos(std::move(pos));
}

ItemInfo* Item::getItemInfo() {
	return info;
}