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

	std::vector<Slot>craftList;
	std::vector<Transform*>craftList_tr;

	int listIndex;
	bool renderFlag;
	CraftingSystem* craftSys;

public:
	Workshop(Manager* mngr_, CraftingSystem* cs);

	void setImg(Entity* entity, Vector2D pos, Vector2D size, std::string name);
	virtual void render();
	virtual void update();
	void setRenderFlag(bool set);
};

