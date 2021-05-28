#pragma once
#include "../ecs/Entity.h"
#include "../ecs/Component.h"
#include "../components/transform.h"
#include "../sdlutils/InputHandler.h"
#include "../ecs/Manager.h"
#include "../classes/workshop.h"
#include "../classes/sleep_station.h"

class Open_station: public Component
{
private:
	Transform* myTr;
	Transform* playerTr;
	Entity* station;

	bool eClicked;

public:
	Open_station(Entity* st);
	void init();
	void update();
};

