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
	lefttime = totaltime; //Recibe los milisegundos de tiempo en raid
	counter = nullptr;
	std::string aux = getHourString(lefttime / 1000);
	lasttime = aux;
	alarm = false;
	cooldown = 0.0f;
}

Countdown::~Countdown() {
	//if (counter != nullptr){
		//delete counter;
	//}
}

void Countdown::render() {
	std::string aux = getHourString(floor(lefttime));
	if (lasttime != aux)//paso de segundos
	{
		soundManager().playSFX("beep"); //beep o tick
		lasttime = aux;
	}
	SDL_Color s;
	if (lefttime <= 0)
	{
		aux = "0:00";
		s = build_sdlcolor(0xff000000);
	}
	else
	{
		s = build_sdlcolor(0xffffffff);
		if (lefttime <= 5.3 && !alarm)
		{
			soundManager().playSFX("alarm");
			alarm = true;
		}
	}
	//delete counter;
	counter = new Texture(sdlutils().renderer(), aux, sdlutils().fonts().at("OrbitronRegular"),
		s);

	counter->render(consts::WINDOW_WIDTH - counter->width() - 10, 10);
	delete counter;
	counter = nullptr;
}

void Countdown::update() {
	lefttime -= consts::DELTA_TIME; //Restamos el tiempoque ha pasado

	//if (cooldown < sdlutils().currRealTime() - 1000 && (auxCount < 5 || lefttime <= 30)) {
	//	soundManager().playSFX("beep"); //beep o tick
	//	cooldown = sdlutils().currRealTime();
	//	auxCount++;
	//}
}