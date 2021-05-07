#pragma once
#include "../classes/workshop.h"

class SpaceshipStation :public Workshop
{
protected:
	Entity* rocketTop;
	Image* rocketTopImg;
	Entity* rocketMid;
	Image* rocketMidImg;
	Entity* rocketBot;
	Image* rocketBotImg;
	
public:
	SpaceshipStation(Manager* realMngr_, Manager* mngr_, CraftingSystem* cs);
	virtual void render();
	virtual void update();
	virtual void rightWindowRender();
	virtual void setWorkshopItems(vector<ITEMS>&& items);
};

