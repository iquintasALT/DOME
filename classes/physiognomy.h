#pragma once
#include <set>
#include "../utils/checkML.h"
#include "player.h"
#include "../game/constant_variables.h"
#include "../classes/lose_scene.h"
#include "../components/player_health_component.h"
#include "../components/wound_comparator.h"

#include "../DomeEvents.h"
class PlayerHealthComponent;
class BleedoutComponent;
class BloodlossComponent;
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
	int* bloodlossCount = nullptr;
	std::multiset<PlayerHealthComponent*, WoundComparator> healthComponents;
	HypothermiaComponent* hypothermia;
	bool playerAlive;

	bool painAdded;
	bool intoxicationAdded;
	bool concussionAdded;

	void checkAlive(WAYSTODIE way = WAYSTODIE::NONE);
public:
	inline Physiognomy(Player* player_) : player(player_), healthComponents(multiset<PlayerHealthComponent*, WoundComparator>()), hypothermia(nullptr) {
		painAdded = false; intoxicationAdded = false; concussionAdded = false; playerAlive = true; }

	//Añadir estados al sistema
	void addBleedout();
	void increaseBloodloss();
	void addPainState();
	void addIntoxicationState();
	void addConcussionState();
	void addHypothermiaState();

	//Borrar estados del sistema
	void removeBleedout();
	void removeBloodloss();
	void removePainState();
	void removeIntoxicationState();
	void removeConcussionState();
	void removeHypothermiaState();

	//Borra todos los estados (cuando se abandona la raid)
	void removeAllStates();
	int getNumStates();

	void die(WAYSTODIE way = WAYSTODIE::NONE);
	inline bool isAlive() const;
	inline std::multiset<PlayerHealthComponent*, WoundComparator>* getHealthComponents() { return &healthComponents; }

	std::list<Wound> getWounds();
};
