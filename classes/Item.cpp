#include "Item.h"
#include "../classes/player.h"
#include "../classes/physiognomy.h"

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
		static_cast<Player*>(player)->getPhysiognomy()->removePainState();
	};

	return new ItemInfo(WATER, "Scarce item, use it carefully", 1, 2, 4, 0, f);
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
	return new ItemInfo(CLASSIC_AMMO, "Security-grade rubber-coated bullets. It wasn't hard to remove the rubber coating. Funny how that works out.", 1, 1, 1, 2);
}

ItemInfo* ItemInfo::ricochetAmmo()
{
	return new ItemInfo(RICOCHET_AMMO, "A spool of high-density polyethylene filament. The printing factories are all out of commission, but this can still be used as ammo for a POLYMER RIFLE.", 1, 1, 1, 2);
}

ItemInfo* ItemInfo::laserAmmo()
{
	return new ItemInfo(LASER_AMMO, "A stable high-discharge battery, used to power a MINING LASER.", 1, 1, 1, 2);
}

//&sdlutils().images().at("items")

Item::Item(ItemInfo* itemInformation, Manager* mngr, Inventory* inventory, int xPos, int yPos, int count) :
	info(itemInformation), x(xPos), y(yPos), count(count) {

	width = info->width();
	height = info->height();
	image = mngr->addEntity();
	mngr->addRenderLayer<Item>(image);
	transform = image->addComponent<Transform>(inventory->itemPosition(x, y),
		Inventory::itemWidth * width, Inventory::itemHeight * height, 0);
	image->addComponent<Image>(&sdlutils().images().at("items"), 8, 3, info->row(), info->col(), true);
	image->setActive(false);

	if (count > 0) {
		auto n = mngr->addEntity();
		mngr->addRenderLayer<Item>(n);
		float w = Inventory::itemWidth * (width - 0.3);
		float h = Inventory::itemHeight * (height - 0.3);
		numberTr = n->addComponent<Transform>(inventory->itemPosition(x, y) + Vector2D(w, h),
			Inventory::itemWidth * 0.3, Inventory::itemHeight * 0.3, 0);
		n->addComponent<Image>(new Texture(sdlutils().renderer(), std::to_string(count), sdlutils().fonts().at("OrbitronBold32"), build_sdlcolor(0xffffff)), true);
		n->setActive(false);
	}
	else numberTr = nullptr;
}

Item::Item(Item* item, Inventory* inventory) {
	info = item->info;
	width = item->width;
	height = item->height;
	x = item->x;
	y = item->y;
	count = item->count;
	numberTr = nullptr;

	if (inventory != nullptr) {
		Manager* mngr = inventory->entity_->getMngr();
		image = mngr->addEntity();
		mngr->addRenderLayer<Item>(image);
		transform = image->addComponent<Transform>(inventory->itemPosition(x, y),
			Inventory::itemWidth * width, Inventory::itemHeight * height, 0);
		image->addComponent<Image>(&sdlutils().images().at("items"), 6, 3, info->row(), info->col(), true);
		image->setActive(false);

		if (count > 0) {
			auto n = mngr->addEntity();
			mngr->addRenderLayer<Item>(n);
			float w = Inventory::itemWidth * (width - 0.3);
			float h = Inventory::itemHeight * (height - 0.3);
			numberTr = n->addComponent<Transform>(inventory->itemPosition(x + w, y + h),
				w, h, 0);
			n->addComponent<Image>(new Texture(sdlutils().renderer(), std::to_string(count), sdlutils().fonts().at("OrbitronBold32"), build_sdlcolor(0xffffff)), true);
			n->setActive(false);
		}
		else numberTr = nullptr;
	}
	else {
		image = nullptr;
		transform = nullptr;
		numberTr = nullptr;
	}
}

Item::~Item() {
	delete info;
	if (image != nullptr)
		image->setDead(true);
	if (numberTr != nullptr)
		image->setDead(true);
}

void Item::render() {
	if (image != nullptr) {
		image->setActive(true);
		image->render();
		image->setActive(false);
	}
}

void Item::update() {
	image->setActive(true);
	image->update();
	image->setActive(false);
}

void Item::setPosition(Vector2D&& pos) {
	transform->setPos(std::move(pos));

	float w = Inventory::itemWidth * (width - 0.3);
	float h = Inventory::itemHeight * (height - 0.3);

	if (numberTr != nullptr)
		numberTr->setPos(pos + Vector2D(w, h));
}

ItemInfo* Item::getItemInfo() {
	return info;
}