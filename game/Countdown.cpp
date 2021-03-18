#include "countdown.h"

std::string getHourString(int lefttime) {
	int min = lefttime / 60;
	int sec = lefttime % 60;

	std::string aux = std::to_string(min) + ":";

	if (sec < 10) aux += "0";
	aux += std::to_string(sec);

	return aux;
}

Countdown::Countdown(int totaltime)
{
	lefttime = totaltime; //Recibe los milisegundos de tiempo en raid
	starttime = SDL_GetTicks();
	updatetime = SDL_GetTicks();

	std::string aux = getHourString(lefttime / 1000);

}

Countdown::~Countdown() {
	delete counter;
}

void Countdown::render() {
	std::string aux = getHourString(lefttime / 1000);
	if (lefttime <= 0)
	{
		aux = "Llamalo Angel, Carlos Leon";
	}

	//delete counter;
	counter = new Texture(sdlutils().renderer(), aux, sdlutils().fonts().at("ARIAL24"),
		build_sdlcolor(0xffffffff));

	counter->render(50, 10);
	delete counter;
	counter = nullptr;
}

void Countdown::update()
{
	lefttime -= SDL_GetTicks() - starttime; //Restamos el tiempoque ha pasado
	starttime = SDL_GetTicks();

}
