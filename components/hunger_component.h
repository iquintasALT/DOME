#pragma once
#include "player_health_component.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "../game/checkML.h"
#include "../utils/Vector2D.h"

/*
* HungerComponent es un component para el jugador que mide su nivel de hambre.
* Afecta a la raid, de tal manera que con un bajo nivel de hambre las heridas que provoquen desangrado
* o efectos acumulativos, su velocidad de acumulaci�n aumentar�.
* Depnde de tres niveles de hambre en los que el jugador se puede encontrar (APENAS HAMBRIENTO, HAMBRIENTO, MUY HAMBRIENTO)
* En el estado MUY HAMBRIENTO, las da�os que reciba el jugador empeorar�n muy r�pido y ser�n de dificil curaci�n.
*/

const float NONEHUNGER_LEVEL = 0.75f; //Por encinma del 75% estar� en NONE y por debajo en HUNGER
const float HUNGER_LEVEL = 0.35f; //Por encima del 35% estar� en HUNGER y por debajo en STARVING

enum class hungerLevel { NONE, HUNGRY, STARVING };

class HungerComponent : public PlayerHealthComponent
{
public:
	HungerComponent() : hunger(1.0f), hungerLevel(hungerLevel::NONE) {};
	void init() override;
	void updateLevel();

	void eat(float hunger_);
private:
	float hunger;
	hungerLevel hungerLevel;
	//Puntero a los componentes de da�o en raid a los que afecte el hambre (acumulativos) para aumentarles el tiempo de acumulacion en base al nivel de hambre
};

