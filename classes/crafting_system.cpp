#include "crafting_system.h"

CraftingSystem::CraftingSystem(Manager* mngr) {
	playerInventory = mngr->getHandler<Player_hdlr>()->getComponent<Inventory>();

	//CAMBIAR A ENUM
	crafts.emplace(BANDAGE, std::vector<I>{I{ MEDICAL_COMPONENTS,1 }, I{ WATER,1 }, I{ ORGANIC_MATERIAL ,1 }});

	crafts.emplace(ANTIDOTE, std::vector<I>{I{ FOOD,1 }, I{ WATER,1 }, I{ MEDICAL_COMPONENTS,1 }});

	crafts.emplace(SPLINT, std::vector<I>{I{ MECANICAL_COMPONENTS,1 }, I{ WATER ,1 }});

	crafts.emplace(SPACESHIP_ROCKETS, std::vector<I>{I{SPACESHIP_KEY_ITEMS ,1 },
		I{ BUILDING_PARTS ,1 }, I{ ELECTRONIC_REMAINS,1 }, I{ METAL_PLATES ,1 }});

	crafts.emplace(WEAPON_UPGRADE, std::vector<I>{I{ MECANICAL_COMPONENTS,1 }, I{ ELECTRONIC_REMAINS,1 }, I{ UPGRADE_KIT,1 }});

	crafts.emplace(CLASSIC_AMMO, std::vector<I>{I{ MECANICAL_COMPONENTS ,1 }, I{ MEDICAL_COMPONENTS,1 }, I{ METAL_PLATES,1 }});

	crafts.emplace(BACKPACK_UPGRADE, std::vector<I>{I{ ORGANIC_MATERIAL,1 }, I{ BANDAGE ,1 }, I{ UPGRADE_KIT,1 }});

	crafts.emplace(METAL_PLATES, std::vector<I>{I{ BUILDING_PARTS,1 }, I{ MECANICAL_COMPONENTS ,1 }});

	crafts.emplace(ARMOUR_UPGRADE, std::vector<I>{I{ METAL_PLATES ,1 }, I{ ORGANIC_MATERIAL ,1 }, I{ UPGRADE_KIT,1 }});
}

void CraftingSystem::CraftItem(std::string item) {
	vector<I> itemsNeeded = (*crafts.find(item)).second;
	list<Item*> itemsList = playerInventory->getItems();
	list<Item*> itemsToDelete;

	bool affordable = true;
	for (Item* invItem : itemsList) {
		string nameToFind = invItem->getItemInfo()->name();

		/*for (int i = 0; i < itemsNeeded.size(); ++i) {
			if (nameToFind == itemsNeeded[i].name) {
				itemsNeeded[i].cantidad--; itemsToDelete.push_back(invItem);
				if (itemsNeeded[i].cantidad <= 0)itemsNeeded.erase(itemsNeeded.begin() + i);
			}
		}*/
	}

	if (itemsNeeded.size() == 0) {
		for (Item* i : itemsToDelete)
			playerInventory->removeItem(i);
		//playerInventory->storeItem() //CREAR ITEM CON ENUMS PARA ALMACENARLO (PENDIENTE DE HACER CON YOJHAN <3)
	}
}

Crafts* CraftingSystem::getCrafts() { return &crafts; }