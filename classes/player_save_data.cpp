#include "player_save_data.h"

#include "../game/Game.h"

#include "../classes/player.h"
#include "../classes/weapon_behaviour.h"

#include "../components/inventory_controller.h"
#include "../components/hunger_component.h"
#include "../components/tiredness_component.h"


PlayerSaveData::PlayerSaveData()
{
	isSaved = false;
}

PlayerSaveData::~PlayerSaveData()
{
	for (auto item : itemsSaved) {
		delete item;
	}
	itemsSaved.clear();
}

void PlayerSaveData::save(Player* p)
{
	if (p->getMngr()->getGame()->currentScene == SCENES::TUTORIAL)
		return;

	isSaved = true;

	//Items
	if (itemsSaved.size() > 0) {
		for (auto item : itemsSaved)
			delete item;
		itemsSaved.clear();
	}

	for (auto item : p->getComponent<InventoryController>()->inventory->getItems())
		itemsSaved.push_back(new ItemSaveData(item));

	//Weapons
	auto weapon = p->getWeapon();

	auto arrAux = weapon->tiersOfWeapons();
	for (int i = 0; i < 3; i++)
		weaponTiers[i] = arrAux[i];

	//Hunger/Tiredness
	hunger = p->getComponent<HungerComponent>()->getHunger();
	tiredness = p->getComponent<TirednessComponent>()->getTirednessFloat();
}

void PlayerSaveData::load(Player* p)
{
	if (!isSaved) return;

	//Items
	auto inventory = p->getComponent<InventoryController>()->inventory;

	for (auto item : inventory->getItems()) {
		inventory->removeItem(item);
		delete item;
	}
	inventory->getItems().clear();

	for (auto item : itemsSaved) {
		inventory->storeItem(item->createItem(inventory));
	}

	//Weapons
	auto weapon = p->getWeapon();
	weapon->updateWeapons(weaponTiers);

	//Hunger/Tiredness
	p->getComponent<HungerComponent>()->setHunger(hunger);
	p->getComponent<TirednessComponent>()->setTirednessFloat(tiredness);
}

void PlayerSaveData::reset()
{
	isSaved = false;
}

void PlayerSaveData::updateTiredness(float decTiredness)
{
	tiredness - decTiredness < 0.0f ? tiredness = 0.0f : tiredness -= decTiredness;
}

PlayerSaveData::ItemSaveData::ItemSaveData(Item* item)
{
	info = new ItemInfo(item->getItemInfo());
	x = item->getX();
	y = item->getY();
	count = item->count;
}

PlayerSaveData::ItemSaveData::~ItemSaveData()
{
	delete info;
}

Item* PlayerSaveData::ItemSaveData::createItem(Inventory* inv)
{
	return new Item(new ItemInfo(info), inv->getEntity()->getMngr(), inv, x, y, count);
}
