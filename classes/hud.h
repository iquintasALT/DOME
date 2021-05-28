#pragma once
#include <list>
#include "../components/transform.h"
#include "player.h"
#include "countdown.h"
#include "../utils/Vector2D.h"
#include "../utils/checkML.h"
#include <vector>
#include <string>

class TextWithBackground;
class Image;

class hud : public Entity
{
private:
	struct _tooltip_{
		Transform* t;
		TextWithBackground* text;
	};
	Transform* posCam;
	Player* player;
	Countdown* time;

	bool frozen = false;
	int bullets = 0;
	int magSize = 0;
	int totalBullet = 0;
	std::list<PlayerHealthComponent*>* states;

	Texture* nbullets;
	Texture* ncharger;
	Texture* totalBullets;
	Texture* timer;
	Texture* marco;
	Texture* stateBackground;
	Texture* stateBackgroundRed;
	Image* currentWeapon;

	std::vector<std::string> woundDescriptions;

	Transform* tooltipTr;
	TextWithBackground* tooltipText;
	int numberOfWounds;
	void drawStatus(int pos, int frameIndex, Vector2D mouse);
	std::vector<_tooltip_> tooltipTextures;
public:
	hud(Manager* m, Transform* initialPos, Player* p, Countdown* time);

	void update() override;

	void render() override;

	void chooseWeapon(int type, int tier);

	void createStatesBackgrounds();

	~hud() { delete posCam; }
};