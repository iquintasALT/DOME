#include "Item.h"

ItemInfo* ItemInfo::bottleOfWater()
{
	return new ItemInfo("Bottle of water", "Scarse item, use it carefully", 1, 2,
		&sdlutils().images().at("player"));
}


Item::Item(ItemInfo* itemInformation, int xPos, int yPos) :
	info(itemInformation), x(xPos), y(yPos) {

	width = info->width();
	height = info->height();
	image = new Image(info->texture());
}

Item::~Item() {
	delete info;
	delete image;
}

void Item::update() {
	image->update();
}