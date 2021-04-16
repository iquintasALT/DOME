#pragma once
#include "../classes/game_entity.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Image.h"
#include "../components/Transform.h"
#include "../ecs/Entity.h"
#include "../classes/crafting_system.h"
#include "../sdlutils/InputHandler.h"
#include "../utils/Collisions.h"
#include "../utils/checkML.h"
#include "../components/InventoryController.h"
#include <vector>

struct Slot {
	int index;
	Entity* slot;
};

class Workshop : public GameEntity
{
private:
	Entity* bg;
	Transform* bg_tr;
	Entity* bButton;
	Transform* bButton_tr;
	Entity* arrowUp;
	Transform* arrowUp_tr;
	Entity* arrowDown;
	Transform* arrowDown_tr;
	Entity* craftButton;
	Transform* craftButton_tr;

	std::vector<Slot>craftList;
	std::vector<Transform*>craftList_tr;

	int listIndex;
	bool renderFlag;

	bool renderRightWindow;
	int	 rightWindowIndex;

	bool mouseClick;
	CraftingSystem* craftSys;
	std::vector<ITEMS> workshopItems;
	Inventory* playerInv;

	Loot* loot;

public:
	Workshop(Manager* realMngr_, Manager* mngr_, CraftingSystem* cs);

	void setWorkshopItems(vector<ITEMS>&& items);
	void setImg(Entity* entity, Vector2D pos, Vector2D size, std::string name);
	void renderImg(float posX, float posY, int row, int col, int sizeX = 64, int sizeY = 64);
	virtual void render();
	void rightWindowRender();
	virtual void update();
	void setRenderFlag(bool set);

	void setLoot(Loot* l) {
		loot = l;
	}
};

