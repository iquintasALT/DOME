#pragma once
#include "../utils/Vector2D.h"
#include "../utils/checkML.h"
#include "player.h"
#include "../classes/countdown.h"
#include "../components/Transform.h"
class hud
{
private:
	Transform* posCam;
	Player* player;
	Countdown* time;

	int bullets = 0;

	Texture* nbullets;
	Texture* ncharger;
public:
	hud(Transform* initialPos, Player* p);

	void init();

	void update();

	void render();

	~hud() { delete time; }
};

