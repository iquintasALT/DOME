#pragma once
#include <list>
#include "../components/Transform.h"
#include "player.h"
#include "countdown.h"
#include "../utils/Vector2D.h"
#include "../utils/checkML.h"

class TextWithBackground;
class hud : public Entity
{
private:
	Transform* posCam;
	Player* player;
	Countdown* time;

	int bullets = 0;
	int charger = 0;
	int totalBullet = 0;
	list<PlayerHealthComponent*>* states;

	Texture* nbullets;
	Texture* ncharger;
	Texture* totalBullets;
	Texture* timer;
	Texture* actweapon;

	Transform* tooltipTr;
	TextWithBackground* tooltipText;
	void drawStatus(int pos, int frameIndex, Vector2D mouse);

public:
	hud(Manager* m, Transform* initialPos, Player* p);

	void update() override;

	void render() override;

	void chooseWeapon(int type, int tier);

	~hud() { delete time; delete posCam; }
};