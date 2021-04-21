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
	int charger = 0;
	int totalBullet = 0;
	vector<PlayerHealthComponent*>* states;

	Texture* nbullets;
	Texture* ncharger;
	Texture* totalBullets;
	Texture* timer;
public:
	hud(Manager* m, Transform* initialPos, Player* p);

	void update() override;

	void render() override;

	~hud() { delete time; 
	delete posCam;
	}
};

