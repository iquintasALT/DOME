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
public:
	Physiognomy(Player* player_) : player(player_) {};
	~Physiognomy() {};

	template<typename T, typename ...Ts>
	void addState(Ts &&... args) {
		auto c = player->addComponent<T>(args);
		healthComponents.push_back(c);
	}

	template<typename T>
	void addState() {
		auto c = player->addComponent<T>();
	    healthComponents.push_back(c);
	}

	template<typename T>
	void removeState(T* comp) {
		player->removeComponent<T>();
		healthComponents.remove(comp);
	}

	bool alive();

private:
	Player* player;
	list<PlayerHealthComponent*> healthComponents;
};

