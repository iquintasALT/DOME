#include "Item.h"

ItemInfo::ItemInfo(ITEMS name, string description, int width, int height, Texture* texture) :
	_name(name), _description(description), _width(width), _height(height), _texture(texture) {};

ItemInfo* ItemInfo::bottleOfWater()
{
	return new ItemInfo(WATER, "Scarse item, use it carefully", 1, 2,
		&sdlutils().images().at("panel"));
}
ItemInfo* ItemInfo::medicine()
{
	return new ItemInfo(ANTIDOTE, "Mmmmmm", 2, 2,
		&sdlutils().images().at("panel"));
}
ItemInfo* ItemInfo::food()
{
	return new ItemInfo(FOOD, "I dont know what im doing", 1, 1,
		&sdlutils().images().at("panel"));
}


Item::Item(ItemInfo* itemInformation, Manager* mngr, Inventory* inventory, int xPos, int yPos) :
	info(itemInformation), x(xPos), y(yPos) {

	width = info->width();
	height = info->height();
	image = mngr->addEntity();
	mngr->addRenderLayer<Item>(image);
	transform = image->addComponent<Transform>(inventory->itemPosition(x, y),
		Inventory::itemWidth * width, Inventory::itemHeight * height, 0);
	image->addComponent<Image>(info->texture());

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