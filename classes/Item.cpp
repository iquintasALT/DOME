#include "Item.h"

ItemInfo::ItemInfo(ITEMS name, string description, int width, int height, int row, int col) :
	_name(name), _description(description), _width(width), _height(height), _row(row), _col(col) {};

ItemInfo* ItemInfo::bottleOfWater()
{
	return new ItemInfo(WATER, "Scarse item, use it carefully", 1, 2, 4, 0);
}
ItemInfo* ItemInfo::medicine()
{
	return new ItemInfo(ANTIDOTE, "Mmmmmm", 2, 2, 0, 1);
}
ItemInfo* ItemInfo::food()
{
	return new ItemInfo(FOOD, "I dont know what im doing", 1, 1, 1, 2);
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
	image->addComponent<Image>(&sdlutils().images().at("items"), 6, 3, info->row(), info->col());

	image->setActive(false);
}

Item::~Item() {
	delete info;
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