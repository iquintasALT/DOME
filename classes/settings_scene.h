#pragma once
#include "game_scene.h"
#include "pause_button.h"

const int VOLUME_LEVELS = 6;

class Game;
class SettingsScene : public GameScene
{
private:
	Transform* createVolumeBar(Vector2D pos, Vector2D size, CallBackOnClick* raise, CallBackOnClick* decrease, Texture* t);
	Vector2D posBarVolume;  Vector2D posBarSFX;
	float currentVolume;  float currentSFXVolume;
	Transform* adjusterVolume; Transform* adjusterSFXVolume;
public:
	SettingsScene(Game* g) : GameScene(g, "Settings") {
		currentVolume = 0; currentSFXVolume = 0;
		adjusterVolume = nullptr; adjusterSFXVolume = nullptr;
	};
	void init() override;
	void moveAdjuster(Vector2D mousePos);

	static void back(Manager* mng);
	static void raiseVolume(Manager* mng);
	static void decreaseVolume(Manager* mng);


	static void raiseEffectsVolume(Manager* mng);
	static void decreaseEffectsVolume(Manager* mng);
};
