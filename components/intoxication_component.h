#pragma once
#include "player_health_component.h"
#include "../game/checkML.h"
#include "../game/constant_variables.h"
class KeyboardPlayerCtrl;
class Player;
class Physiognomy;
class HungerComponent;

/*
* IntoxicationComponent es un da�o que puede recibir el jugador si se adentra en zonas con radiaci�n o gases t�xicos.
* Es temporal, es decir, el jugador puede decidir esperar que automaticamente desaparecza o curarlo.
* Afecta al hambre del jugador.
*/

class IntoxicationComponent : public PlayerHealthComponent
{
private:
	int time;
	int timeToApplyHunger;
	Physiognomy* phys;
	HungerComponent* hunger;
public:
	IntoxicationComponent() : time(0), timeToApplyHunger(0), phys(nullptr), hunger(nullptr){};
	~IntoxicationComponent() {};
	void init() override;
	void update() override;

	void newState();
	void increaseTime(int time);
};

