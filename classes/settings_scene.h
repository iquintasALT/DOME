#pragma once
#include "game_scene.h"
class Game;

class SettingsScene : public GameScene
{
private:
	void createVolumeBar(Vector2D pos, Vector2D size);
public:
	SettingsScene(Game* g) : GameScene(g, "Settings") {};
	void init() override;

	static void back(Manager* mng);
	static void raiseVolume(Manager* mng);
	static void decreaseVolume(Manager* mng);
};

