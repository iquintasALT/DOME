#include "Item.h"
#include "../classes/player.h"
#include "../classes/physiognomy.h"
#include "../components/hunger_component.h"
#include "../sdlutils/SoundManager.h"

#include "../DomeEvents/Heal.h"

#include "GlassHouse.h"

ItemInfo::ItemInfo(ITEMS name, string strName, string description, int width, int height, int row, int col, int craftAmount) :
	_name(name), _strName(strName), _description(description), _width(width), _height(height), _row(row), _col(col), _craftAmount(craftAmount) {
	function = [](Entity*) {return true; };
	functionCreated = false;
};

ItemInfo::ItemInfo(ITEMS name, string strName, string description, int width, int height, int row, int col, std::function<bool(Entity* p)> f, int craftAmount) :
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

ItemInfo::~ItemInfo() {}

ItemInfo* ItemInfo::antidote()
{
	auto f = [](Entity* player) 
	{
		bool success = player->getComponent<IntoxicationComponent>();
		bool intoxication = player->getComponent<IntoxicationComponent>();

		GlassHouse::enqueue(new Heal(success, intoxication));

		static_cast<Player*>(player)->getPhysiognomy()->removeIntoxicationState();
		return true;
	};

	return new ItemInfo(ANTIDOTE, "antidote", "General-use antidote, made from 82.1% natural ingrdients.", 2, 2, 1, 0, f);
}

ItemInfo* ItemInfo::bandage()
{
	auto f = [](Entity* player) {

		bool success = player->getComponent<BleedoutComponent>(); 
		bool intoxication = player->getComponent<IntoxicationComponent>(); 

		GlassHouse::enqueue(new Heal(success, intoxication));

		static_cast<Player*>(player)->getPhysiognomy()->removeBleedout();
		soundManager().playSFX("heal");
		return true; // CAMBIA
	};

	return new ItemInfo(BANDAGE, "bandage", "Clean bandages for treating bloodloss.", 1, 1, 0, 2, f);
}

ItemInfo* ItemInfo::medicalComponents()
{
	return new ItemInfo(MEDICAL_COMPONENTS, "medical components", "Hard-to-synthesize antiseptics, useful for making more potent medicines.", 1, 2, 0, 1);
}


ItemInfo* ItemInfo::water()
{
	return new ItemInfo(WATER, "water", "Pure water, bottled on Earth. Still manages to taste wrong.", 1, 2, 4, 0);

}

ItemInfo* ItemInfo::organicMaterial()
{
	return new ItemInfo(ORGANIC_MATERIAL, "organic material", "I... can't eat this yet, but I've seen a synthesizer turn worse into food.", 2, 2, 0, 0);
}

ItemInfo* ItemInfo::mechanicalComponents()
{
	return new ItemInfo(MECHANICAL_COMPONENTS, "mechanical components", "Parts salvaged from broken machinery.", 2, 1, 4, 1);
}

ItemInfo* ItemInfo::spaceshipRockets()
{
	return new ItemInfo(SPACESHIP_ROCKETS, "spaceship rockets", "Important part of the spaceship.", 1, 1, 6, 0);
}

ItemInfo* ItemInfo::spaceshipKeyItem()
{
	return new ItemInfo(SPACESHIP_KEY_ITEMS, "spaceship key item", "A critical component from an escape shuttle. Why would they take this?", 2, 2, 4, 2);
}

ItemInfo* ItemInfo::metalScraps()
{
	return new ItemInfo(METAL_SCRAPS, "metal scraps", "Rended scraps of metal. A little work on the kiln could make them usable again.", 2, 2, 7, 0);
}

ItemInfo* ItemInfo::electronicRemains() {
	return new ItemInfo(ELECTRONIC_REMAINS, "electronic remains", "Miscellaneous circuitboards and electrical components from a worker's wiring practice kit.", 1, 1, 5, 0);
}

ItemInfo* ItemInfo::spaceshipRadar() {
	return new ItemInfo(SPACESHIP_RADAR, "spaceship radar", "Important part of the spaceship.", 1, 1, 5, 2);
}

ItemInfo* ItemInfo::spaceshipCabin() {
	return new ItemInfo(SPACESHIP_CABIN, "spaceship cabin", "Important part of the spaceship.", 1, 1, 6, 1);
}

ItemInfo* ItemInfo::weaponUpgrade() {
	return new ItemInfo(WEAPON_UPGRADE, "weapon upgrade", "Lorem ipsum?", 1, 1, 7, 2);
}

ItemInfo* ItemInfo::upgradeKit() {
	return new ItemInfo(UPGRADE_KIT, "upgrade kit", "Advanced weapon parts. These must have come from Security. Is anywhere safe from those creatures?", 2, 2, 6, 2);
}

ItemInfo* ItemInfo::splint()
{
	auto f = [](Entity* player) {
		
		bool success = player->getComponent<ConcussionComponent>();
		bool intoxication = player->getComponent<IntoxicationComponent>();

		GlassHouse::enqueue(new Heal(success, intoxication));

		static_cast<Player*>(player)->getPhysiognomy()->removeConcussionState();
		soundManager().playSFX("splint");
		return true; //CAMBIAA
	};

	return new ItemInfo(SPLINT, "splint", "Self-molding splint, for treating fractured bones.", 2, 2, 5, 1, f);
}


ItemInfo* ItemInfo::painKiller()
{
	auto f = [](Entity* player) 
	{		
		bool success = player->getComponent<PainComponent>();
		bool intoxication = player->getComponent<IntoxicationComponent>();

		GlassHouse::enqueue(new Heal(success, intoxication));

		static_cast<Player*>(player)->getPhysiognomy()->removePainState();
		soundManager().playSFX("pills");
		return true; //CAMBIAA
	};

	return new ItemInfo(PAINKILLER, "painkiller", "Local anaesthetic. Cures pain. Side efects may include mild pains. Huh.", 1, 2, 2, 0, f);
}


ItemInfo* ItemInfo::food()
{
	auto f = [](Entity* player) {
		if (player->getMngr()->getGame()->currentScene == SCENES::SHELTER) {
			static_cast<Player*>(player)->getComponent<HungerComponent>()->eat(0.20f);
			return true;
		}
		else return false;
	};

	return new ItemInfo(FOOD, "food", "Technically, this is food.", 1, 1, 1, 2, f);
}

ItemInfo* ItemInfo::laserAmmo()
{
	return new ItemInfo(LASER_AMMO, "laser ammo", "Ammunition for mining laser. Miniature sulphur batteries, checked for leaks.", 1, 1, 3, 0);
}

ItemInfo* ItemInfo::ricochetAmmo()
{
	return new ItemInfo(RICOCHET_AMMO, "ricochet ammo", "Ammunition for grenade launchers. Explosive charges, with a bouncy plastic coating.", 1, 1, 3, 1);
}

ItemInfo* ItemInfo::classicAmmo()
{
	return new ItemInfo(CLASSIC_AMMO, "classic ammo", "Ammunition for standard firearms. We were told Security used rubber bullets, but this is heavy lead after all.", 1, 1, 2, 1);
}

ItemInfo* ItemInfo::metalPlates()
{
	return new ItemInfo(METAL_PLATES, "metal plates", "Polished metal plating for the fuselage of an escape shuttle.", 2, 2, 7, 1);
}

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
	textureNumber = nullptr;
	if (count > 0) {
		countTex = mngr->addEntity();
		mngr->addRenderLayer<Item>(countTex);
		float w = Inventory::itemWidth * (width - 0.3);
		float h = Inventory::itemHeight * (height - 0.3);
		numberTr = countTex->addComponent<Transform>(inventory->itemPosition(x, y) + Vector2D(w, h),
			Inventory::itemWidth * 0.3, Inventory::itemHeight * 0.3, 0);
		textureNumber = new Texture(sdlutils().renderer()
			, std::to_string(count), sdlutils().fonts().at("OrbitronBold32")
			, build_sdlcolor(0xffffff));
		countTex->addComponent<Image>(textureNumber, true);
		countTex->setActive(false);
	}
	else numberTr = nullptr;
}

Item::Item(Item* item, Inventory* inventory) :
	Item(new ItemInfo(item->getItemInfo()), inventory->getEntity()->getMngr(), inventory,
		item->x, item->y, item->count) {
}

Item::~Item() {
	delete info;

	if (countTex != nullptr && !forceDelete) {
		countTex->setDead(true);
	}

	if (textureNumber != nullptr) {
		delete textureNumber;
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