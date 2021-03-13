#include "../classes/game_state_machine.h"

//destructora de la maquina de estados
GameStateMachine::~GameStateMachine() {
	while (!states.empty()) popState(); //eliminamos cada estado
}

//metodo para cambiar a un estado especifico
void GameStateMachine::changeState(GameScene* gs) {
	popState(); //quitamos el estado actual
	pushState(gs); //agregamos el nuevo estado
}

//metodo para quitar un estado de la cima de la pila
void GameStateMachine::popState() {
	//si hay estados, eliminamos su memoria y lo sacamos de la pila
	if (!states.empty()) { 
		delete states.top();
		states.pop();
	}
}