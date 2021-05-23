#include "crafting_system.h"
#include "../classes/workshop.h"
#include "../sdlutils/SoundManager.h"

CraftingSystem::CraftingSystem(Manager* mngr) {
	playerInventory = mngr->getHandler<Player_hdlr>()->getComponent<InventoryController>()->inventory;

	//CAMBIAR A ENUM
	crafts.emplace(BANDAGE, std::vector<I>{I(MEDICAL_COMPONENTS, 1), I(WATER, 1), I(ORGANIC_MATERIAL, 1)});

	crafts.emplace(ANTIDOTE, std::vector<I>{I(FOOD, 1), I(WATER, 1), I(MEDICAL_COMPONENTS, 1)});

	crafts.emplace(SPLINT, std::vector<I>{I(MECANICAL_COMPONENTS, 1), I(WATER, 1)});

	crafts.emplace(PAINKILLER, std::vector<I>{I(FOOD, 2), I(WATER, 1), I(MEDICAL_COMPONENTS, 2)});

	crafts.emplace(FOOD, std::vector<I>{I(ORGANIC_MATERIAL, 1), I(WATER, 1)});

	crafts.emplace(WEAPON_UPGRADE, std::vector<I>{I(MECANICAL_COMPONENTS, 1), I(ELECTRONIC_REMAINS, 1), I(UPGRADE_KIT, 1)});

	crafts.emplace(CLASSIC_AMMO, std::vector<I>{I(MECANICAL_COMPONENTS, 1), I(MEDICAL_COMPONENTS, 1), I(METAL_PLATES, 1)});
	crafts.emplace(LASER_AMMO, std::vector<I>{I(CLASSIC_AMMO, 1), I(ELECTRONIC_REMAINS, 2)});
	crafts.emplace(RICOCHET_AMMO, std::vector<I>{I(CLASSIC_AMMO, 1), I(MECANICAL_COMPONENTS, 2)});


	crafts.emplace(METAL_PLATES, std::vector<I>{I(BUILDING_PARTS, 1), I(MECANICAL_COMPONENTS, 1) });

	crafts.emplace(SPACESHIP_CABIN, std::vector<I>{I(SPACESHIP_KEY_ITEMS, 3), I(METAL_PLATES, 2)});
	crafts.emplace(SPACESHIP_RADAR, std::vector<I>{I(SPACESHIP_KEY_ITEMS, 1)});
	crafts.emplace(SPACESHIP_ROCKETS, std::vector<I>{I(SPACESHIP_KEY_ITEMS, 2)});

}

bool CraftingSystem::CraftItem(ITEMS item, int x, int y, Workshop* ws, bool openLoot) {
	itemsToDelete.clear();

	vector<I> itemsNeeded = (*crafts.find(item)).second;
	list<Item*> itemsList = playerInventory->getItems();

	bool affordable = true;
	for (Item* invItem : itemsList) {
		ITEMS nameToFind = invItem->getItemInfo()->name();

		for (int i = 0; i < itemsNeeded.size(); ++i) {
			if (nameToFind == itemsNeeded[i].name) {
				itemsNeeded[i].cantidad--; itemsToDelete.push_back(invItem);
				if (itemsNeeded[i].cantidad <= 0)itemsNeeded.erase(itemsNeeded.begin() + i);
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

ItemInfo* CraftingSystem::getItemInfo(ITEMS item) {
	switch (item)
	{
	case BANDAGE:
		return ItemInfo::bandage();
		break;
	case ANTIDOTE:
		return ItemInfo::antidote();
		break;
	case FOOD:
		return ItemInfo::food();
		break;
	case SPLINT:
		return ItemInfo::splint();
		break;
	case METAL_PLATES:
		return ItemInfo::metalPlates();
		break;
	case CLASSIC_AMMO:
		return ItemInfo::classicAmmo();
		break;
	case RICOCHET_AMMO:
		return ItemInfo::ricochetAmmo();
		break;
	case LASER_AMMO:
		return ItemInfo::laserAmmo();
		break;
	case PAINKILLER:
		return ItemInfo::painKiller();
		break;
	default:
		return 0;
		break;
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