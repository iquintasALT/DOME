#pragma once
#include<iostream>
#include <SDL.h>
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/checkML.h"

class Countdown
{
private:
	float timeLeft;
	Texture* counter;
	bool alarm;
	float cooldown;
	int auxCount;
public:
	Countdown(int totaltime);
	virtual ~Countdown();
	void update();
	void render();

	inline bool keepPlaying() { return timeLeft > 0; }

	inline float getTime() const { return timeLeft; }
};
