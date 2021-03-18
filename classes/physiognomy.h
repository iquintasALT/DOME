#pragma once
#include <vector>
#include "../components/player_health_component.h"
#include "../game/checkML.h"

using namespace std;

const float MAX_HEALTH = 100;
class Physiognomy
{
public:
	Physiognomy() : health(MAX_HEALTH){};
	~Physiognomy() {};

	void harm(float damage);
	void heal(float life);
	bool alive();
	inline float getHealth() { return health; }
	inline void setHealth(float h) { health = h; }

	/*
	* Implementar m�todos que aumenten, disminuyan, o permitan consultar un componente
	* de fisionomia del jugador (comida, bebida, descanso, hambre, sed)
	* 
	* Adem�s, ya que se contiene una lista para guardar los componentes
	* se implementar� un m�todo que los a�ada a dicha lista (a�adirlos en un orden especifico ayudar� 
	* a programar la logica)
	* 
	* void addState(Player_health_component* state) {
		states.push_back(state);
	}
	*/

private:
	float health;

	/*
	* Futuros atributos representando el nivel de cada estado
	* 
	* float thirst;
	* float hunger;
	* float rest;
	* float contusion;
	* 
	* Futura lista de punteros a componentes de fisonomia del jugador
	* vector<Player_health_component*> states;
	*/
};

