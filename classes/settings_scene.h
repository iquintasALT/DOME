#pragma once
#include "game_scene.h"
#include "pause_button.h"

class Game;
class SettingsScene : public GameScene
{
private:
	Transform* createVolumeBar(Vector2D pos, Vector2D size, CallBackOnClick* raise, CallBackOnClick* decrease, Texture* t);
	void createShowFPSBar();
	Vector2D posBarVolume;  Vector2D posBarSFX;
	float currentVolume;  float currentSFXVolume;
	Transform* adjusterVolume; Transform* adjusterSFXVolume;
public:
	SettingsScene(Game* g) : GameScene(g, "Settings") {
		currentVolume = 0; currentSFXVolume = 0;
		adjusterVolume = nullptr; adjusterSFXVolume = nullptr;
	};
	void init() override;
	void setAdjusterPosition();

	static void back(Manager* mng);
	static void raiseVolume(Manager* mng);
	static void decreaseVolume(Manager* mng);
	static void raiseEffectsVolume(Manager* mng);
	static void decreaseEffectsVolume(Manager* mng);
	static void showFPS(Manager* mng);
};

class CreditsScene :public GameScene {
public:
	CreditsScene(Game* g);
	void init() override;
};