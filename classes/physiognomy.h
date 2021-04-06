#pragma once
#include <vector>
#include "../components/player_health_component.h"
#include "../game/checkML.h"
#include <list>
#include "player.h"
#include "../game/constant_variables.h"
class PlayerHealthComponent;
using namespace std;

/*
* La fisonomia del jugador es un sistema que se encarga de los da�os que puede sufrir el jugador durante una raid.
* Por lo tanto, los estados de refugio (hambre y cansacio) no se manejan en este sistema, simplemente se a�aden al principio de la escena
* Sin embargo, estados como el desangrado, hipotermia, etc.. son a�adidos exclusivamente durante las raid.
* Al volver al refugio despues de una raid, se anulan todos estos da�os.
* Si el numero de estados es mayor que un n�mero m�ximo determinado, el jugador muere.
*/

class Physiognomy {
private:
	Player* player;
	list<PlayerHealthComponent*> healthComponents;

public:
	inline Physiognomy(Player* player_) : player(player_) {};
	inline ~Physiognomy() {};

	template<typename T, typename ...Ts>
	inline void addState(Ts &&... args) {
		auto c = player->addComponent<T>(args);
		healthComponents.push_back(c);
	}

	template<typename T>
	inline void addState() {
		auto c = player->addComponent<T>();
	    healthComponents.push_back(c);
	}

	template<typename T>
	inline void removeState(T* comp) {
		player->removeComponent<T>();
		healthComponents.remove(comp);
	}

	inline bool alive() { return healthComponents.size() < consts::MAX_MULTIPLE_STATES; };
	inline list<PlayerHealthComponent*>* getHealthComponents() { return &healthComponents; }
};

