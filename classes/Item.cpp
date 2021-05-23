#include "Item.h"
#include "../classes/player.h"
#include "../classes/physiognomy.h"
#include "../components/hunger_component.h"

ItemInfo::ItemInfo(ITEMS name, string description, int width, int height, int row, int col):
	_name(name), _description(description), _width(width), _height(height), _row(row), _col(col) {
	function = [](Entity*) {};
	functionCreated = false;
};


ItemInfo::ItemInfo(ITEMS name, string description, int width, int height, int row, int col, std::function<void(Entity* p)> f) :
	_name(name), _description(description), _width(width), _height(height), _row(row), _col(col), function(f), functionCreated(true) {
};

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

	return new ItemInfo(BANDAGE, "Can heal bleeding", 1, 1, 0, 2, f);
}

ItemInfo* ItemInfo::splint()
{
	auto f = [](Entity* player) {
		static_cast<Player*>(player)->getPhysiognomy()->removeConcussionState();
	};

	return new ItemInfo(SPLINT, "Can heal concussions",2, 1, 5, 1, f);
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
		static_cast<Player*>(player)->getComponent<HungerComponent>()->eat(0.34f);
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


ItemInfo* ItemInfo::water()
{
	auto f = [](Entity* player) {
	};

	return new ItemInfo(WATER, "Drink, used for medical recipes", 1, 2, 4, 0, f);
}

ItemInfo* ItemInfo::medicalComponents()
{
	auto f = [](Entity* player) {
	};

	return new ItemInfo(MEDICAL_COMPONENTS, "Medical components used in multiple healing crafts", 1, 2, 0, 1, f);
}

ItemInfo* ItemInfo::organicMaterial()
{
	auto f = [](Entity* player) {
	};

	return new ItemInfo(ORGANIC_MATERIAL, "Organic material used on some crafts", 2, 2, 2, 0, f);
}

ItemInfo* ItemInfo::mechanicalComponents()
{
	auto f = [](Entity* player) {
	};

	return new ItemInfo(MECANICAL_COMPONENTS, "Mechanical components used on crafts", 1, 1, 4, 1, f);
}

ItemInfo* ItemInfo::buildingParts()
{
	auto f = [](Entity* player) {
	};

	return new ItemInfo(BUILDING_PARTS, "Building parts used on crafts", 2, 2, 7, 0, f);
}

ItemInfo* ItemInfo::electronicalRemains()
{
	auto f = [](Entity* player) {
	};

	return new ItemInfo(ELECTRONIC_REMAINS, "Building parts used on crafts", 1, 1, 5, 0, f);
}

ItemInfo* ItemInfo::upgradeKit()
{
	auto f = [](Entity* player) {
	};

	return new ItemInfo(UPGRADE_KIT, "Building parts used on crafts", 3, 3, 6, 2, f);
}

ItemInfo* ItemInfo::spaceshipKeyItem()
{
	auto f = [](Entity* player) {
	};

	return new ItemInfo(SPACESHIP_KEY_ITEMS, "Key item to repair the spaceship", 3, 3, 4, 2, f);
}

ItemInfo* ItemInfo::metalPlates()
{
	auto f = [](Entity* player) {
	};

	return new ItemInfo(METAL_PLATES, "Metal plates to repair the spaceship", 2, 2, 7, 1, f);
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

Item::Item(Item* item, Inventory* inventory) :
	Item(item->getItemInfo(), inventory->getEntity()->getMngr(), inventory,
		item->x, item->y, item->count) {

}

Item::~Item() {
	delete info;

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