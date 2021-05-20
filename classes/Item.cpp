#include "Item.h"
#include "../classes/player.h"
#include "../classes/physiognomy.h"
#include "../components/hunger_component.h"

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
//ITEMS name, string description, int width, int height, int row, int col, std::function<void(Entity*)> function = [](Entity*) {});


ItemInfo* ItemInfo::antidote()
{
	auto f = [](Entity* player) {
		static_cast<Player*>(player)->getPhysiognomy()->removeIntoxicationState();
	};

	return new ItemInfo(ANTIDOTE, "Can heal intoxication", 2, 2, 1, 0, f);
}

ItemInfo* ItemInfo::bandage()
{
	auto f = [](Entity* player) {
		static_cast<Player*>(player)->getPhysiognomy()->removeBleedState();
	};

	return new ItemInfo(BANDAGE, "Can heal bleeding", 2, 1, 0, 2, f);
}

ItemInfo* ItemInfo::splint()
{
	auto f = [](Entity* player) {
		static_cast<Player*>(player)->getPhysiognomy()->removeConcussionState();
	};

	return new ItemInfo(SPLINT, "Can heal concussions", 2, 2, 5, 1, f);
}

ItemInfo* ItemInfo::painKiller()
{
	auto f = [](Entity* player) {
		static_cast<Player*>(player)->getPhysiognomy()->removePainState();
	};

	return new ItemInfo(PAINKILLER, "Can heal pain", 1, 2, 0, 0, f);
}


ItemInfo* ItemInfo::food()
{
	auto f = [](Entity* player) {
		static_cast<Player*>(player)->getComponent<HungerComponent>()->eat(0.20f);
	};

	return new ItemInfo(FOOD, "Good item against hunger", 1, 1, 1, 2, f);
}

ItemInfo* ItemInfo::laserAmmo()
{
	auto f = [](Entity* player) {
	};

	return new ItemInfo(LASER_AMMO, "High technology to use in the laser weapon", 1, 1, 3, 0, f);
}

ItemInfo* ItemInfo::ricochetAmmo()
{
	auto f = [](Entity* player) {
	};

	return new ItemInfo(RICOCHET_AMMO, "Bullets covered in a bouncing alien material for the ricochet weapon", 1, 1, 3, 1, f);
}

ItemInfo* ItemInfo::classicAmmo()
{
	auto f = [](Entity* player) {
	};

	return new ItemInfo(CLASSIC_AMMO, "Bullets for the classic weapon", 1, 1, 2, 1, f);
}

ItemInfo* ItemInfo::metalPlates()
{
	auto f = [](Entity* player) {
	};

	return new ItemInfo(METAL_PLATES, "Metal plates", 2, 2, 7, 1, f);
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
	tex = nullptr;
	if (count > 0) {
		auto n = mngr->addEntity();
		mngr->addRenderLayer<Item>(n);
		float w = Inventory::itemWidth * (width - 0.3);
		float h = Inventory::itemHeight * (height - 0.3);
		numberTr = n->addComponent<Transform>(inventory->itemPosition(x, y) + Vector2D(w, h),
			Inventory::itemWidth * 0.3, Inventory::itemHeight * 0.3, 0);
		tex = new Texture(sdlutils().renderer(), std::to_string(count), sdlutils().fonts().at("OrbitronBold32"), build_sdlcolor(0xffffff));
		n->addComponent<Image>(tex, true);
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
	tex = nullptr;

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
			tex = new Texture(sdlutils().renderer(), std::to_string(count), sdlutils().fonts().at("OrbitronBold32"), build_sdlcolor(0xffffff));
			n->addComponent<Image>(tex, true);
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
		numberTr->getEntity()->setDead(true);

	if (tex != nullptr)
		delete tex;
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