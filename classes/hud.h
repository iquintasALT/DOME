#pragma once
#include "../utils/Vector2D.h"
#include "../utils/checkML.h"
#include "player.h"
#include "../classes/countdown.h"
#include "../components/Transform.h"
class hud: public Entity
{
private:
	Transform* posCam;
	Player* player;
	Countdown* time;

	int bullets = 0;

	Texture* nbullets;
	Texture* ncharger;
	Texture* state1;
	Texture* state2;
public:
	hud(Manager* m, Transform* initialPos, Player* p);

	void init();

	void update() override;

	void render() override;


	~hud() { delete time; }
};

