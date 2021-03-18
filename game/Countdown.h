#pragma once
#include<iostream>
#include <SDL.h>
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "../game/checkML.h"

class Countdown
{
public:
	Countdown(int totaltime);
	virtual ~Countdown();
	void update();
	void render();

	bool keepPlaying() { return lefttime > 0; }

private:
	int lefttime;
	int starttime;
	int updatetime;
	Texture* counter;
};
