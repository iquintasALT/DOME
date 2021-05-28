#pragma once

#include "../components/player_health_component.h"

#include <list>

/*
* TirednessComponent es un componente para el jugador que mide su nivel de cansacio.
* Afecta a su velocidad de movimiento y cuanto menos duerma el jugador, el nivel 
* de cansancio del jugador aumentar� y subira de nivel, habiendo tres niveles
* (Apenas cansado, cansado y exhausto).
* Si est� exhasuto la velocidad de movimiento es tan baja que el jugador apenas podr� moverse.
*/

enum class TirednessLevel { NONE, TIRED, EXHAUSTED };

class KeyboardPlayerCtrl;

class TirednessComponent : public PlayerHealthComponent
{
private:
	float tiredness;
	KeyboardPlayerCtrl* kb;
	TirednessLevel tirednessLev;

public:
	TirednessComponent();
	void init() override;
	void updateLevel();					//Actualiza el nivel de cansacio de jugador en base a su cansancio
	void calculatePlayerSpeed() const; //Calcula velocidad del jugador en base a su cansancio y la modifica (velocidad del transform)
	 
	void sleep(int hours);			    //Horas descansadas como parametro
	void decreaseTiredness(float tiredness);
	TirednessLevel getTirednessLevel() { return tirednessLev; }
	float getTirednessFloat() { return tiredness; }
	void setTirednessFloat(float tiredness_);
};
