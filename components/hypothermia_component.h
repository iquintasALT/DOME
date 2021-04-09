#pragma once
#include "player_health_component.h"

/*
* HypothermiaComponent es un componente de daño que va a parte del sistema de daño en raid.
* A partir de un cierto momento del dia (atardeciendo/anocheciendo) en la raid, este estado de hipotermia aparece.
* A medida que va avanzando el tiempo, el jugador tiene mas frio y el nivel de hipotermia aumenta.
* Si el jugador no se ha ido de la raid en el momento en el que cae la noche, morirá.
* Es de alguna forma un limitador de tiempo en raid.
*/

class HypothermiaComponent : public PlayerHealthComponent
{
private:
	float hypothermia;
public:
	HypothermiaComponent() : hypothermia(0){}
	void init() override;
};

