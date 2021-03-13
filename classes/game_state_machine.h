#ifndef GAMESTATEMACHINE_H_
#define GAMESTATEMACHINE_H_

#include "../classes/game_scene.h"
#include <stack>

using namespace std;

class GameStateMachine
{
private:
	stack<GameScene*> states; //pila de estados

public:
	~GameStateMachine();
	void changeState(GameScene* gs);
	//metodo para obtener el estado en el que nos encontramos
	GameScene* currentState() { return states.top(); };
	void popState();
	//metodo para agregar nuevo estado a la cola
	void pushState(GameScene* gs) { states.push(gs); };
};
#endif