#include "Item.h"
#include "../classes/player.h"
#include "../classes/physiognomy.h"
#include "../components/hunger_component.h"

ItemInfo::ItemInfo(ITEMS name, string strName, string description, int width, int height, int row, int col, int craftAmount) :
	_name(name), _strName(strName), _description(description), _width(width), _height(height), _row(row), _col(col), _craftAmount(craftAmount) {
	function = [](Entity*) {};
	functionCreated = false;
};


ItemInfo::ItemInfo(ITEMS name, string strName, string description, int width, int height, int row, int col, std::function<void(Entity* p)> f, int craftAmount) :
	_name(name), _strName(strName), _description(description), _width(width), _height(height), _row(row), _col(col), function(f), functionCreated(true), _craftAmount(craftAmount) {
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



ItemInfo* ItemInfo::antidote()
{
	auto f = [](Entity* player) {
		static_cast<Player*>(player)->getPhysiognomy()->removeIntoxicationState();
	};

	return new ItemInfo(ANTIDOTE, "antidote", "Can heal intoxication", 2, 2, 1, 0, f);
}

ItemInfo* ItemInfo::bandage()
{
	auto f = [](Entity* player) {
		static_cast<Player*>(player)->getPhysiognomy()->removeBleedState();
	};

	return new ItemInfo(BANDAGE, "bandage", "Can heal bleeding", 1, 1, 0, 2, f);
}

ItemInfo* ItemInfo::medicalComponents()
{
	return new ItemInfo(MEDICAL_COMPONENTS, "medical components", "Useful to craft medicines", 1, 2, 0, 1);
}


ItemInfo* ItemInfo::water()
{
	return new ItemInfo(WATER, "water", "Good to craft some medicines", 1, 2, 4, 0);

}

ItemInfo* ItemInfo::organicMaterial()
{
	return new ItemInfo(ORGANIC_MATERIAL, "organic material", "Useful to craft medicines or food", 2, 2, 1, 2);
}

ItemInfo* ItemInfo::mecanicalComponents()
{
	return new ItemInfo(MECANICAL_COMPONENTS, "mecanical components", "I could craft something with this...", 2, 1, 4, 1);
}

ItemInfo* ItemInfo::spaceshipRockets()
{
	return new ItemInfo(SPACESHIP_ROCKETS, "spaceship rockets", "Important part of the spaceship", 1, 1, 6, 0);
}


ItemInfo* ItemInfo::spaceshipKeyItem()
{
	return new ItemInfo(SPACESHIP_KEY_ITEMS, "spaceship key item", "I could build spaceship parts with this", 2, 2, 4, 2);
}

ItemInfo* ItemInfo::buildingParts()
{
	return new ItemInfo(BUILDING_PARTS, "building parts", "I could craft something with this...", 2, 2, 7, 0);
}

ItemInfo* ItemInfo::electronicRemains() {
	return new ItemInfo(ELECTRONIC_REMAINS, "electronic remains", "I could craft something with this...", 1, 1, 5, 0);
}

ItemInfo* ItemInfo::spaceshipRadar() {
	return new ItemInfo(SPACESHIP_RADAR, "spaceship radar", "Important part of the spaceship", 1, 1, 5, 2);
}

ItemInfo* ItemInfo::spaceshipCabin() {
	return new ItemInfo(SPACESHIP_CABIN, "spaceship cabin", "Important part of the spaceship", 1, 1, 6, 1);
}

ItemInfo* ItemInfo::weaponUpgrade() {
	return new ItemInfo(WEAPON_UPGRADE, "weapon upgrade", "Weapon upgrade", 1, 1, 7, 2);
}

ItemInfo* ItemInfo::upgradeKit() {
	return new ItemInfo(UPGRADE_KIT, "upgrade kit", "Perfect tools to improve my weapons!", 2, 2, 6, 2);
}

ItemInfo* ItemInfo::splint()
{
	auto f = [](Entity* player) {
		static_cast<Player*>(player)->getPhysiognomy()->removeConcussionState();
	};

	return new ItemInfo(SPLINT, "splint", "Can heal concussions", 2, 2, 5, 1, f);
}


ItemInfo* ItemInfo::painKiller()
{
	auto f = [](Entity* player) {
		static_cast<Player*>(player)->getPhysiognomy()->removePainState();
	};

	return new ItemInfo(PAINKILLER, "painkiller", "Can heal pain", 1, 2, 0, 0, f);
}


ItemInfo* ItemInfo::food()
{
	auto f = [](Entity* player) {
		static_cast<Player*>(player)->getComponent<HungerComponent>()->eat(0.20f);
	};

	return new ItemInfo(FOOD, "food", "Food, reduces hunger", 1, 1, 1, 2, f);
}

ItemInfo* ItemInfo::laserAmmo()
{
	return new ItemInfo(LASER_AMMO, "laser ammo", "High technology to use in the laser weapon", 1, 1, 3, 0);
}

ItemInfo* ItemInfo::ricochetAmmo()
{
	return new ItemInfo(RICOCHET_AMMO, "ricochet ammo", "Bullets covered in a bouncing alien material for the ricochet weapon", 1, 1, 3, 1);
}

ItemInfo* ItemInfo::classicAmmo()
{
	return new ItemInfo(CLASSIC_AMMO, "classic ammo", "Bullets for the classic weapon", 1, 1, 2, 1);
}

ItemInfo* ItemInfo::metalPlates()
{
	return new ItemInfo(METAL_PLATES, "metal plates", "Metal plates, useful to repair the spaceship", 2, 2, 7, 1);
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
	countTex = nullptr;
	if (count > 0) {
		countTex = mngr->addEntity();
		mngr->addRenderLayer<Item>(countTex);
		float w = Inventory::itemWidth * (width - 0.3);
		float h = Inventory::itemHeight * (height - 0.3);
		numberTr = countTex->addComponent<Transform>(inventory->itemPosition(x, y) + Vector2D(w, h),
			Inventory::itemWidth * 0.3, Inventory::itemHeight * 0.3, 0);
		countTex->addComponent<Image>(new Texture(sdlutils().renderer(), std::to_string(count), sdlutils().fonts().at("OrbitronBold32"), build_sdlcolor(0xffffff)), true);
		countTex->setActive(false);
	}
	else numberTr = nullptr;
}

Item::Item(Item* item, Inventory* inventory) :
	Item(item->getItemInfo(), inventory->getEntity()->getMngr(), inventory,
		item->x, item->y, item->count) {

}

Item::~Item() {
	delete info;

	if (countTex != nullptr) {
		countTex->setDead(true);
	}
		
}

void Item::removeImage()
{
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