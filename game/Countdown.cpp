#include "countdown.h"

Countdown::Countdown(int totaltime)
{
	lefttime = totaltime; //Recibe los milisegundos de tiempo en raid
	starttime = SDL_GetTicks();
	updatetime = SDL_GetTicks();
}

void Countdown::update()
{
	lefttime -= SDL_GetTicks() - starttime; //Restamos el tiempoque ha pasado
	starttime = SDL_GetTicks();

	if (lefttime <= 0)
	{
		std::cout << "Carlos Leon llamalo Angel";
	}
	else if (updatetime + 1000 <= SDL_GetTicks())
	{
		updatetime = SDL_GetTicks();
		int seg = lefttime / 1000;
		int min = seg / 60;
		seg = seg % 60;
		if (min < 10)
		{
			std::cout << "0" << min;
		}
		else
		{
			std::cout << min;
		}
		std::cout << ":";
		if (seg < 10)
		{
			std::cout << "0" << seg << std::endl;
		}
		else
		{
			std::cout << seg << std::endl;
		}
	}
}