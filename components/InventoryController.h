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
#include "../game/checkML.h"

class InventoryController: public Component
{
public :
	InventoryController();
	~InventoryController();

	void update() override;
	void init() override;
	void Use();
protected:
	bool isOpen = false;
	Entity* inventoryPanel = nullptr;
	KeyboardPlayerCtrl* playerMovement = nullptr;
	Weapon* playerWeapon = nullptr;

private:
	bool used = false;
};

