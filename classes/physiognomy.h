#pragma once
#include <list>
#include "../utils/checkML.h"
#include "player.h"
#include "../game/constant_variables.h"
#include "../classes/lose_scene.h"
class PlayerHealthComponent;
class BleedoutComponent;
class PainComponent;
class ContussionComponent;
class IntoxicationComponent;
class HypothermiaComponent;
class LoseScene;

/*
* La fisonomia del jugador es un sistema que se encarga de los da�os que puede sufrir el jugador durante una raid.
* Por lo tanto, los estados de refugio (hambre y cansacio) no se manejan en este sistema, simplemente se a�aden al principio de la escena
* Sin embargo, estados como el desangrado, contusion, etc.. son a�adidos exclusivamente durante las raid.
* Al volver al refugio despues de una raid, se anulan todos estos da�os.
* Si el numero de estados es mayor que un n�mero m�ximo determinado, el jugador muere.
*/

class Physiognomy {
private:
	Player* player;
	std::list<PlayerHealthComponent*> healthComponents;
	HypothermiaComponent* hypothermia;
	bool playerAlive;

	int numBleedStates;
	bool painAdded;
	bool intoxicationAdded;
	bool concussionAdded;

	void checkAlive(WAYSTODIE way = WAYSTODIE::NONE);
public:
	inline Physiognomy(Player* player_) : player(player_), healthComponents(list<PlayerHealthComponent*>()), hypothermia(nullptr) {
		numBleedStates = 0; painAdded = false; intoxicationAdded = false; concussionAdded = false; playerAlive = true; }

	//Añadir estados al sistema
	void addBleedState();
	void addPainState();
	void addIntoxicationState();
	void addConcussionState();
	void addHypothermiaState();

	//Borrar estados del sistema
	void removeBleedState();
	void removePainState();
	void removeIntoxicationState();
	void removeConcussionState();
	void removeHypothermiaState();

	//Borra todos los estados (cuando se abandona la raid)
	void removeAllStates();
	int getNumStates() { return healthComponents.size(); }
	int getNumBleedStates() { return numBleedStates; }
	int getNumUniqueStates() { return healthComponents.size() - numBleedStates + (numBleedStates > 0); };

	void die(WAYSTODIE way = WAYSTODIE::NONE);
	inline bool isAlive() const;
	inline std::list<PlayerHealthComponent*>* getHealthComponents() { return &healthComponents; }
};
