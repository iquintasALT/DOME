#pragma once
#include <vector>
#include "../components/player_health_component.h"
#include "../game/checkML.h"
#include <list>
#include "player.h"
class PlayerHealthComponent;
using namespace std;

const int MAX_MULTIPLE_STATES = 7;

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

	inline bool alive() { return healthComponents.size() < MAX_MULTIPLE_STATES; };
	inline list<PlayerHealthComponent*>* getHealthComponents() { return &healthComponents; }
};

