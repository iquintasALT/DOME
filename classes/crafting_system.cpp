#include "crafting_system.h"
#include "../classes/workshop.h"
#include "../sdlutils/SoundManager.h"

CraftingSystem::CraftingSystem(Manager* mngr) {
	playerInventory = mngr->getHandler<Player_hdlr>()->getComponent<InventoryController>()->inventory;

	//CAMBIAR A ENUM
	crafts.emplace(BANDAGE, std::vector<ItemInfo>{getItemInfo(BANDAGE, 1), getItemInfo(WATER, 1), getItemInfo(ORGANIC_MATERIAL, 1)});

	crafts.emplace(ANTIDOTE, std::vector<ItemInfo>{getItemInfo(FOOD, 1), getItemInfo(WATER, 1), getItemInfo(MEDICAL_COMPONENTS, 1)});

	crafts.emplace(SPLINT, std::vector<ItemInfo>{getItemInfo(MECANICAL_COMPONENTS, 1), getItemInfo(WATER, 1)});

	crafts.emplace(PAINKILLER, std::vector<ItemInfo>{getItemInfo(FOOD, 2), getItemInfo(WATER, 1), getItemInfo(MEDICAL_COMPONENTS, 2)});

	crafts.emplace(FOOD, std::vector<ItemInfo>{getItemInfo(ORGANIC_MATERIAL, 1), getItemInfo(WATER, 1)});

	crafts.emplace(WEAPON_UPGRADE, std::vector<ItemInfo>{getItemInfo(MECANICAL_COMPONENTS, 1), getItemInfo(ELECTRONIC_REMAINS, 1), getItemInfo(UPGRADE_KIT, 1)});

	crafts.emplace(CLASSIC_AMMO, std::vector<ItemInfo>{getItemInfo(MECANICAL_COMPONENTS, 1), getItemInfo(MEDICAL_COMPONENTS, 1), getItemInfo(METAL_PLATES, 1)});
	crafts.emplace(LASER_AMMO, std::vector<ItemInfo>{getItemInfo(CLASSIC_AMMO, 1), getItemInfo(ELECTRONIC_REMAINS, 2)});
	crafts.emplace(RICOCHET_AMMO, std::vector<ItemInfo >{getItemInfo(CLASSIC_AMMO, 1), getItemInfo(MECANICAL_COMPONENTS, 2)});


	crafts.emplace(METAL_PLATES, std::vector<ItemInfo>{getItemInfo(BUILDING_PARTS, 1), getItemInfo(MECANICAL_COMPONENTS, 1) });

	crafts.emplace(SPACESHIP_CABIN, std::vector<ItemInfo>{getItemInfo(SPACESHIP_KEY_ITEMS, 3), getItemInfo(METAL_PLATES, 2)});
	crafts.emplace(SPACESHIP_RADAR, std::vector<ItemInfo>{getItemInfo(SPACESHIP_KEY_ITEMS, 1), getItemInfo(METAL_PLATES, 1)});
	crafts.emplace(SPACESHIP_ROCKETS, std::vector<ItemInfo>{getItemInfo(SPACESHIP_KEY_ITEMS, 2)});

}

bool CraftingSystem::CraftItem(ITEMS item, int x, int y, Workshop* ws, bool openLoot) {
	itemsToDelete.clear();

	vector<ItemInfo> itemsNeeded = (*crafts.find(item)).second;
	list<Item*> itemsList = playerInventory->getItems();

	bool affordable = true;
	for (Item* invItem : itemsList) {
		ITEMS nameToFind = invItem->getItemInfo()->name();

		for (int i = 0; i < itemsNeeded.size(); ++i) {
			if (nameToFind == itemsNeeded[i].name()) {
				itemsNeeded[i].setAmount(itemsNeeded[i].getAmount() - 1); itemsToDelete.push_back(invItem);
				if (itemsNeeded[i].getAmount() <= 0)itemsNeeded.erase(itemsNeeded.begin() + i);
			}
		}
	}

	if (itemsNeeded.size() == 0) {
		if (openLoot) {
			Entity* auxEntity = playerInventory->getEntity()->getMngr()->addEntity();
			ItemInfo* info = getItemInfo(item);
			auxEntity->addComponent<Transform>(Vector2D(x, y), info->width(), info->height(), 0);
			Loot* invAux = auxEntity->addComponent<Loot>("Press E to open the loot", info->width(), info->height());
			invAux->getInventory()->storeItem(new Item{ info,auxEntity->getMngr(),invAux->getInventory(),0,0 });
			invAux->Interact();

			soundManager().playSFX("build");
			ws->setLoot(invAux);
		}
		return true;
	}
	else return false;
}

//enum ITEMS {
//	BANDAGE, MEDICAL_COMPONENTS, WATER, ORGANIC_MATERIAL, MECANICAL_COMPONENTS, ANTIDOTE, FOOD, SPLINT, SPACESHIP_ROCKETS, SPACESHIP_KEY_ITEMS,
//	BUILDING_PARTS, ELECTRONIC_REMAINS, METAL_PLATES, WEAPON_UPGRADE, UPGRADE_KIT, CLASSIC_AMMO, RICOCHET_AMMO, LASER_AMMO, SPACESHIP_RADAR, SPACESHIP_CABIN
//	, PAINKILLER
//};

ItemInfo* CraftingSystem::getItemInfo(ITEMS item, int amount) {
	ItemInfo* aux;
	switch (item)
	{
	case SPACESHIP_CABIN: {
		aux = ItemInfo::spaceshipCabin();
		aux->setAmount(amount);
		return aux;
		break;
	}
	case SPACESHIP_RADAR: {
		aux = ItemInfo::spaceshipRadar();
		aux->setAmount(amount);
		return aux;
		break;
	}
	case UPGRADE_KIT:
	{
		aux = ItemInfo::upgradeKit();
		aux->setAmount(amount);
		return aux;
		break;
	}
	case WEAPON_UPGRADE:
	{
		aux = ItemInfo::weaponUpgrade();
		aux->setAmount(amount);
		return aux;
		break;
	}
	case ELECTRONIC_REMAINS:
	{
		aux = ItemInfo::electronicRemains();
		aux->setAmount(amount);
		return aux;
		break;
	}
	case BUILDING_PARTS:
	{
		aux = ItemInfo::buildingParts();
		aux->setAmount(amount);
		return aux;
		break;
	}
	case SPACESHIP_KEY_ITEMS:
	{
		aux = ItemInfo::spaceshipKeyItem();
		aux->setAmount(amount);
		return aux;
		break;
	}
	case SPACESHIP_ROCKETS:
	{
		aux = ItemInfo::spaceshipRockets();
		aux->setAmount(amount);
		return aux;
		break;
	}
	case MECANICAL_COMPONENTS:
	{
		aux = ItemInfo::mecanicalComponents();
		aux->setAmount(amount);
		return aux;
		break;
	}
	case ORGANIC_MATERIAL:
	{
		aux = ItemInfo::organicMaterial();
		aux->setAmount(amount);
		return aux;
		break;
	}
	case WATER:
	{
		ItemInfo* aux = ItemInfo::water();
		aux->setAmount(amount);
		return aux;
		break;
	}
	case MEDICAL_COMPONENTS:
	{
		aux = ItemInfo::medicalComponents();
		aux->setAmount(amount);
		return aux;
		break;
	}
	case BANDAGE: {
		aux = ItemInfo::bandage();
		aux->setAmount(amount);
		return aux;
		break;
	}
	case ANTIDOTE:
	{
		aux = ItemInfo::antidote();
		aux->setAmount(amount);
		return aux;
		break;
	}
	case FOOD:
	{
		aux = ItemInfo::food();
		aux->setAmount(amount);
		return aux;
		break;
	}
	case SPLINT:
	{
		aux = ItemInfo::splint();
		aux->setAmount(amount);
		return aux;
		break;
	}
	case METAL_PLATES:
	{
		aux = ItemInfo::metalPlates();
		aux->setAmount(amount);
		return aux;
		break;
	}
	case CLASSIC_AMMO:
	{
		aux = ItemInfo::classicAmmo();
		aux->setAmount(amount);
		return aux;
		break;
	}
	case RICOCHET_AMMO:
	{
		aux = ItemInfo::ricochetAmmo();
		aux->setAmount(amount);
		return aux;
		break;
	}
	case LASER_AMMO:
	{
		aux = ItemInfo::laserAmmo();
		aux->setAmount(amount);
		return aux;
		break;
	}
	case PAINKILLER:
	{
		aux = ItemInfo::painKiller();
		aux->setAmount(amount);
		return aux;
		break;
	}
	default: {
		return nullptr;
		break;
		}
	}
}

void CraftingSystem::FinishCraft() {
	for (Item* i : itemsToDelete) {
		playerInventory->removeItem(i);
		delete i;
	}
	itemsToDelete.clear();
}

Crafts* CraftingSystem::getCrafts() { return &crafts; }