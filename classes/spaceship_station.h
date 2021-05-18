#pragma once
#include "../classes/workshop.h"

class ShelterScene;

class SpaceshipStation :public Workshop
{
protected:
	Entity* rocketTop;
	Image* rocketTopImg;
	Entity* rocketMid;
	Image* rocketMidImg;
	Entity* rocketBot;
	Image* rocketBotImg;
	ShelterScene* shelterScene;

	bool endGame = false;

public:
	SpaceshipStation(Manager* realMngr_, Manager* mngr_, CraftingSystem* cs, ShelterScene* shelterScene_);
	virtual void render();
	virtual void update();
	virtual void rightWindowRender();
	virtual void setWorkshopItems(vector<ITEMS>&& items);
	bool isBuilt() { return endGame; };
};

