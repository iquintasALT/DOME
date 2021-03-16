#include "Item.h"


ItemInfo* ItemInfo::bottleOfWater()
{
	return new ItemInfo("Bottle of water", "Scarse item, use it carefully", 1, 2,
		&sdlutils().images().at("panel"));
}
ItemInfo* ItemInfo::medicine()
{
	return new ItemInfo("Bottle of water", "Scarse item, use it carefully", 1, 1,
		&sdlutils().images().at("panel"));
}


Item::Item(ItemInfo* itemInformation, Manager* mngr, Inventory* inventory, int xPos, int yPos) :
	info(itemInformation), x(xPos), y(yPos) {

	width = info->width();
	height = info->height();
	image = mngr->addEntity();
	transform = image->addComponent<Transform>(inventory->itemPosition(x, y), 
		Vector2D(), inventory->itemWidth * width, inventory->itemHeight * height, 0);
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