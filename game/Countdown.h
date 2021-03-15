#pragma once
#include<iostream>
#include <SDL.h>
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"

class Countdown
{
public:
	Countdown(int totaltime);

	void update();
	void render();

	bool keepPlaying() { return lefttime > 0; }

private:
	int lefttime;
	int starttime;
	int updatetime;
};
