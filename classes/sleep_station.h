#pragma once
#include "../classes/game_object.h"
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
class ShelterScene;
class SleepStation : public GameObject
{
private:
	Entity* bg, * bButton, * leftButton, * rightButton, * clock, * arrow, * sleep0, * sleep1, * sleep2;
	Transform* bg_tr, * bButton_tr, * rightButton_tr, * leftButton_tr, * clock_tr, * arrow_tr, * sleep2_tr, * sleep1_tr, * sleep0_tr;

	Transform* playerTr;
	ShelterScene* shelterScene;
	Texture* text;
	SDL_Rect dest_text;
	Manager* falseMngr;

	bool renderFlag;
	bool mouseClick;

public:
	SleepStation(Manager* realMngr_, Manager* mngr_, ShelterScene* shelterScene_);
	~SleepStation() { delete text; }
	virtual void init();

	void setImg(Entity* entity, Vector2D pos, Vector2D size, std::string name);
	void renderImg(float posX, float posY, int row, int col, int sizeX = 64, int sizeY = 64);
	virtual void render();
	virtual void update();
	void setRenderFlag(bool set);
};



