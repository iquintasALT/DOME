#pragma once
#include "game_scene.h"
#include "pause_button.h"

class Game;
class SettingsScene : public GameScene
{
private:
	Transform* createVolumeBar(Vector2D pos, Vector2D size, CallBackOnClick* raise, CallBackOnClick* decrease, Texture* t);
	void createShowFPSBar();
	void createFullscreenToggle();
	Vector2D posBarVolume;  Vector2D posBarSFX;
	float currentVolume;  float currentSFXVolume;
	Transform* adjusterVolume; Transform* adjusterSFXVolume;
	Texture* buttonBackground;

	//Textos
	Texture* mainVolumeTex;
	Texture* effectsVolumeTex;
	Texture* showFPSTex;

public:
	SettingsScene(Game* g) : GameScene(g, "Settings") {
		currentVolume = 0; currentSFXVolume = 0;
		adjusterVolume = nullptr; adjusterSFXVolume = nullptr;
		buttonBackground = nullptr;
	};
	~SettingsScene() { delete mainVolumeTex; delete effectsVolumeTex; delete showFPSTex; }
	void init() override;
	void render() override;
	void setAdjusterPosition();

	static void back(Manager* mng);
	static void raiseVolume(Manager* mng);
	static void decreaseVolume(Manager* mng);
	static void raiseEffectsVolume(Manager* mng);
	static void decreaseEffectsVolume(Manager* mng);
	static void showFPS(Manager* mng);
	static void fullScreen(Manager* mng);
};

class CreditsScene :public GameScene {
public:
	CreditsScene(Game* g);
	void init() override;
	void update() override;

private:
	bool exit;
	float t;
	float width;
	int margin;

	void addTitle(std::string t, int& y);
	void addText(std::string t, int& y);
	void addParallelTitle(std::string t, std::string t2, int& y);
	void addParallel(std::string t, std::string t2, int& y);

	Entity* holdToSkip;
};