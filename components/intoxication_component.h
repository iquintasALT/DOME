#pragma once
#include "player_health_component.h"
#include "../game/checkML.h"
#include "../game/constant_variables.h"
class KeyboardPlayerCtrl;
class Player;
class Physiognomy;

/*
* IntoxicationComponent es un da�o que puede recibir el jugador si se adentra en zonas con radiaci�n o gases t�xicos.
* Es temporal, es decir, el jugador puede decidir esperar que automaticamente desaparecza o curarlo.
* Afecta al rango en el que los enemigos detectan al jugador, aument�ndolo.
*/

class IntoxicationComponent : public PlayerHealthComponent
{
private:
	int time;
	Physiognomy* phys;
public:
	IntoxicationComponent() : time(0), phys(nullptr){};
	~IntoxicationComponent() {};
	void init() override;
	void update() override;

	void increaseTime(int time);
};

