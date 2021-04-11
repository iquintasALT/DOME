#pragma once
#include "player_health_component.h"
#include "../sdlutils/Texture.h"
class Physiognomy;

/*
* HypothermiaComponent es un componente de daño que va a parte del sistema de daño en raid.
* Cuando se acabe el tiempo de raid, este estado de hipotermia aparece.
* A medida que va avanzando el tiempo, el jugador tiene mas frio y el nivel de hipotermia aumenta.
* Si el jugador no se ha ido de la raid en el momento en el que cae la noche, morirá.
* Es de alguna forma un limitador de tiempo en raid.
*/

class HypothermiaComponent : public PlayerHealthComponent
{
private:
	Texture* frost;
	Physiognomy* phys;
	float hypothermia;
	int time;
public:
	HypothermiaComponent() : hypothermia(0), time(0), phys(nullptr), frost(nullptr){}
	void init() override;
	void update() override;
	void render() override;
};

