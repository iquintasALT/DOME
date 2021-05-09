#pragma once
#include "game_scene.h"
#include "enemy.h"
#include "player.h"
#include "tile.h"
#include "../utils/checkML.h"
#include <string>
class Countdown;
class Player;

class RaidScene : public GameScene
{
private:
	string path_;
	Countdown* timer;
	Player* player;
	bool raidTimeEnded;
public:
	RaidScene(string path, string name, Game* game) : GameScene(game, name) { path_ = path;}
	~RaidScene() { delete timer; }
	void init() override;
	void update() override;
};

