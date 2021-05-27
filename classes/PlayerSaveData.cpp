#include "PlayerSaveData.h"
#include "../classes/player.h"


#include "../components/Transform.h"
#include "../components/player_animation.h"
#include "../components/Image.h"
#include "../components/KeyboardPlayerCtrl.h"
#include "../components/InventoryController.h"
#include "../components/weapon.h"
#include "../components/interactions.h"
#include "../components/particleSystem.h"
#include "../components/bleedout_component.h"
#include "../components/pain_component.h"
#include "../components/concussion_component.h"
#include "../components/intoxication_component.h"
#include "../components/hunger_component.h"
#include "../components/tiredness_component.h"
#include "../components/hypothermia_component.h"
#include "../components/box_collider.h"
#include "../components/CameraMovement.h"
#include "../components/enemy_contact_damege.h"

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
	isSaved = true;

	//Items

	for (auto item : itemsSaved) {
		delete item;
	}
	itemsSaved.clear();

	for (auto item : p->getComponent<InventoryController>()->inventory->getItems()) {
		itemsSaved.push_back(new ItemSaveData(item));
	}

	//Position
	position = p->getComponent<Transform>()->getPos();

	//Hunger

	//Tiredness

	//Weapons

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
}

void PlayerSaveData::clear()
{
	PlayerSaveData::~PlayerSaveData();
	isSaved = false;
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
