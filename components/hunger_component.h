#pragma once
#include "player_health_component.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "../game/checkML.h"
#include "../utils/Vector2D.h"
#include "../game/constant_variables.h"
class BleedoutComponent;

/*
* HungerComponent es un component para el jugador que mide su nivel de hambre.
* Afecta a la raid, de tal manera que con un bajo nivel de hambre las heridas que provoquen desangrado
* o efectos acumulativos, su velocidad de acumulaci�n aumentar�.
* Depnde de tres niveles de hambre en los que el jugador se puede encontrar (APENAS HAMBRIENTO, HAMBRIENTO, MUY HAMBRIENTO)
* En el estado MUY HAMBRIENTO, las da�os que reciba el jugador empeorar�n muy r�pido y ser�n de dificil curaci�n.
*/

enum class hungerLevel { NONE, HUNGRY, STARVING };

class HungerComponent : public PlayerHealthComponent
{
private:
	float hunger;
	hungerLevel hungerLevel;
	BleedoutComponent* bleed;
public:
	HungerComponent();
	void init() override;

	void updateLevel();
	int calculateBleedingSpeed(); //Metodo que se encarga del debufo del hambre (Velocidad de desangrado)
	void setHunger(float hunger);
	void decreaseHunger(float hunger);
	float getHunger();

	void eat(float hunger_);
};

