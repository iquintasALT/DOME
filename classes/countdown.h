#pragma once
#include<iostream>
#include <SDL.h>
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/checkML.h"

class Countdown
{
private:
	int lefttime;
	int starttime;
	int updatetime;
	Texture* counter;

public:
	Countdown(int totaltime);
	virtual ~Countdown();
	void update();
	void render();

	inline bool keepPlaying() { return lefttime > 0; }
};
