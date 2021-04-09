#pragma once
#include <vector>
#include <vector>
#include "../utils/checkML.h"
#include "player.h"
#include "../game/constant_variables.h"
class PlayerHealthComponent;
class BleedoutComponent;
class PainComponent;
class ContussionComponent;
class IntoxicationComponent;
using namespace std;

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
	vector<PlayerHealthComponent*> healthComponents;
	int numStates;

	int numBleedStates;
	bool painAdded;
	bool intoxicationAdded;
	bool concussionAdded;
public:
	inline Physiognomy(Player* player_) : player(player_), healthComponents(consts::MAX_MULTIPLE_STATES) {
		numStates = 0; numBleedStates = 0; painAdded = false; intoxicationAdded = false; concussionAdded = false; };

	//A�adir estados al sistema
	void addBleedState();
	void addPainState();
	void addIntoxicationState();
	void addConcussionState();

	//Borrar estados del sistema
	void removeBleedState();
	void removePainState();
	void removeIntoxicationState();
	void removeConcussionState();

	int getNumStates() { return numStates; }
	void moveElems(int i);

	inline bool alive() { return numStates < consts::MAX_MULTIPLE_STATES; };
	inline vector<PlayerHealthComponent*>* getHealthComponents() { return &healthComponents; }
};
