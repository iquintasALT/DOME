#pragma once
#include "game_scene.h"
#include "enemy.h"
#include "player.h"
#include "../utils/checkML.h"
#include <string>
#include "countdown.h"
class Player;
class Texture;

class RaidScene : public GameScene
{
private:
	string path_;
	Countdown* timer;
	Player* player;
	bool raidTimeEnded;
	void createParallaxBackground(int numOfRep) override;
public:
	RaidScene(string path, string name, Game* game) : GameScene(game, name) { path_ = path;}
	~RaidScene() { delete timer; }
	void init() override;
	void update() override;

	inline float getTime() const { return timer->getTime(); }
};

