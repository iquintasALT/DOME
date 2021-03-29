#include "crafting_system.h"

CraftingSystem::CraftingSystem(Manager* mngr) {
	playerInventory = mngr->getHandler<Player_hdlr>()->getComponent<Inventory>();

	//CAMBIAR A ENUM
	crafts.emplace("bandage", std::vector<I>{I{ "medical_components",1 }, I{ "water",1 }, I{ "organic_material" ,1 }});

	crafts.emplace("antidote", std::vector<I>{I{ "food",1 }, I{ "water",1 }, I{ "medical_components",1 }});

	crafts.emplace("splint", std::vector<I>{I{ "mecanical_components",1 }, I{ "water" ,1 }});

	crafts.emplace("spaceship_rockets", std::vector<I>{I{ "spaceship_key_items" ,1 },
		I{ "building_parts" ,1 }, I{ "electronic_remains",1 }, I{ "metal_plates" ,1 }});

	crafts.emplace("weapon_upgrade", std::vector<I>{I{ "mecanical_components",1 }, I{ "electronic_remains",1 }, I{ "upgrade_kit",1 }});

	crafts.emplace("clasic_ammo", std::vector<I>{I{ "mecanical_components" ,1 }, I{ "medical_components",1 }, I{ "metal_plates",1 }});

	crafts.emplace("backpack_upgrade", std::vector<I>{I{ "organic_material",1 }, I{ "bandage" ,1 }, I{ "upgrade_kit",1 }});

	crafts.emplace("metal_plates", std::vector<I>{I{ "building_parts",1 }, I{ "mecanical_components" ,1 }});

	crafts.emplace("armour_upgrade", std::vector<I>{I{ "metal_plates" ,1 }, I{ "organic_material" ,1 }, I{ "upgrade_kit",1 }});
}

void CraftingSystem::CraftItem(std::string item) {
	vector<I> itemsNeeded = (*crafts.find(item)).second;
	list<Item*> itemsList = playerInventory->getItems();
	list<Item*> itemsToDelete;

	bool affordable = true;
	for (Item* invItem : itemsList) {
		string nameToFind = invItem->getItemInfo()->name();

		for (int i = 0; i < itemsNeeded.size(); ++i) {
			if (nameToFind == itemsNeeded[i].item) {
				itemsNeeded[i].cantidad--; itemsToDelete.push_back(invItem);
				if (itemsNeeded[i].cantidad <= 0)itemsNeeded.erase(itemsNeeded.begin() + i);
			}
		}
	}

	if (itemsNeeded.size() == 0) {
		for (Item* i : itemsToDelete)
			playerInventory->removeItem(i);
			//playerInventory->storeItem() //CREAR ITEM CON ENUMS PARA ALMACENARLO (PENDIENTE DE HACER CON YOJHAN <3)
	}
}