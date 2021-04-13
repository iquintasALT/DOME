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
#include "../components/Inventory.h"
#include <vector>
class SleepStation : public GameEntity
{
	Entity* bg, *bButton, *leftButton, *rightButton, *clock, *arrow, *sleepButton;
	Transform* bg_tr, *bButton_tr, *rightButton_tr, *leftButton_tr, *clock_tr, *arrow_tr;

	bool renderFlag;
	bool mouseClick;

public:
	SleepStation(Manager* mngr_);
	virtual void init();

	void setImg(Entity* entity, Vector2D pos, Vector2D size, std::string name);
	void renderImg(float posX, float posY, int row, int col, int sizeX = 64, int sizeY = 64);
	virtual void render();
	virtual void update();
	void setRenderFlag(bool set);
};



