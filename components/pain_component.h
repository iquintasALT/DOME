#pragma once
#include "player_health_component.h"
#include "../game/checkML.h"
#include "../sdlutils/SDLUtils.h"
class ConcussionComponent;
class IntoxicationComponent;
class Physiognomy;

/*
* PainComponent es un daño en raid que el jugador puede sufrir debido a cortes o mordeduras de los enemigos a melee.
* Afecta al resto de estados temporales aumentando el tiempo de su duración. Cada x tiempo, añade y tiempo a cada daño temporal, siendo y menor que x
* Es un daño permanente que puede ser curado con algun painkiller (item a pensar).
*/

class PainComponent : public PlayerHealthComponent
{
private:
	int time;
	Physiognomy* phys;
public:
	PainComponent() : phys(nullptr), time(0) {};
	void increaseTime();
	void init() override;
	void update() override;
};

