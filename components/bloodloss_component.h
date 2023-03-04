#pragma once
#include "player_health_component.h"
#include "../ecs/Manager.h"
#include "../utils/checkML.h"
#include "../game/constant_variables.h"
class Physiognomy;
class HungerComponent;

/*
* BloodlossComponent es un componente de da�o que puede sufrir el jugador en raid.
* Cada vez que se completa una herida (Bleedout) se le a�ade un nivel de desangrado al jugador.
* No tiene m�s efectos.
*/
class BloodlossComponent : public PlayerHealthComponent
{
private:
	int count = 1;
public:
	BloodlossComponent() {};
	void init() override;
	void update() override {};
	inline int* getCount() { return &count; };
};

