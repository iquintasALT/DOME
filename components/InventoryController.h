#pragma once

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../classes/weapon_behaviour.h"
#include "../components/KeyboardPlayerCtrl.h"
#include "../sdlutils/InputHandler.h"
#include "../components/Image.h"
#include "../components/Transform.h"
#include "../components/Inventory.h"
#include "../classes/player.h"
//#include "../components/weapon.h"
#include "../components/weapon.h"
#include "../utils/checkML.h"
#include "../classes/weapon_behaviour.h"

class InventoryController: public Component
{
private:
	bool used = false;

protected:
	bool isOpen = false;
	Entity* inventoryPanel = nullptr;
	KeyboardPlayerCtrl* playerMovement = nullptr;
	Weapon* playerWeapon = nullptr;

public :
	InventoryController();
	~InventoryController();

	void update() override;
	void init() override;
	void Use();

	void OpenLoot(bool state);


	Inventory* inventory;
};

