#pragma once
#include "game_scene.h"
#include "pause_button.h"

class Game;
class SettingsScene : public GameScene
{
private:
	int a;
	void createVolumeBar(Vector2D pos, Vector2D size, CallBackOnClick* raise, CallBackOnClick* decrease, Texture* t);
public:
	SettingsScene(Game* g) : GameScene(g, "Settings") {};
	void init() override;

	static void back(Manager* mng);
	static void raiseVolume(Manager* mng);
	static void decreaseVolume(Manager* mng);

	static void raiseEffectsVolume(Manager* mng);
	static void decreaseEffectsVolume(Manager* mng);
};

