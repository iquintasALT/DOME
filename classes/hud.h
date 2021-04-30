#pragma once

#include "../components/Transform.h"
#include "player.h"
#include "countdown.h"

#include "../utils/Vector2D.h"
#include "../utils/checkML.h"

class hud : public Entity
{
private:
	Transform* posCam;
	Player* player;
	Countdown* time;

	int bullets = 0;
	int charger = 0;
	int totalBullet = 0;
	vector<PlayerHealthComponent*>* states;

	Texture* nbullets;
	Texture* ncharger;
	Texture* totalBullets;
	Texture* timer;

	void drawStatus(int stateNum, int pos, int frameIndex);

public:
	hud(Manager* m, Transform* initialPos, Player* p);

	void update() override;

	void render() override;

	~hud() { delete time; delete posCam; }
};