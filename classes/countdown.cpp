#include "countdown.h"

#include "../game/constant_variables.h"
#include "../sdlutils/SoundManager.h"
using namespace std;

std::string getHourString(int lefttime) {
	int min = lefttime / 60;
	int sec = lefttime % 60;

	std::string aux = std::to_string(min) + ":";

	if (sec < 10) aux += "0";
	aux += std::to_string(sec);
	
	return aux;
}

Countdown::Countdown(int totaltime) {
	timeLeft = totaltime; //Recibe los milisegundos de tiempo en raid
	counter = nullptr;
	std::string aux = getHourString(timeLeft / 1000);
	
	alarm = false;
	cooldown = 0.0f;
	auxCount = 0;
}

Countdown::~Countdown() {
	//if (counter != nullptr){
		//delete counter;
	//}
}

void Countdown::render() {
	std::string aux = getHourString(floor(timeLeft));
	
	SDL_Color s;
	if (timeLeft <= 0)
	{
		aux = "0:00";
		s = build_sdlcolor(0xff000000);
	}
	else
	{
		s = build_sdlcolor(0xffffffff);
	}
	//delete counter;
	counter = new Texture(sdlutils().renderer(), aux, sdlutils().fonts().at("OrbitronRegular"),
		s);

	counter->render(consts::WINDOW_WIDTH - counter->width() - 10, 10);
	delete counter;
	counter = nullptr;
}

void Countdown::update() {
	timeLeft -= consts::DELTA_TIME; //Restamos el tiempoque ha pasado

	if (cooldown < sdlutils().currRealTime() - 1000 && (auxCount < 5 || (timeLeft <= 30 && timeLeft >5))) {
		soundManager().playSFX("beep"); //beep o tick
		cooldown = sdlutils().currRealTime();
		auxCount++;
	}
}