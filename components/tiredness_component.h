#pragma once
#include "player_health_component.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/checkML.h"
#include "../utils/Vector2D.h"
#include "../components/Transform.h"
#include "../components/KeyboardPlayerCtrl.h"
#include "../game/constant_variables.h"
#include <list>

/*
* TirednessComponent es un componente para el jugador que mide su nivel de cansacio.
* Afecta a su velocidad de movimiento y cuanto menos duerma el jugador, el nivel 
* de cansancio del jugador aumentará y subira de nivel, habiendo tres niveles
* (Apenas cansado, cansado y exhausto).
* Si está exhasuto la velocidad de movimiento es tan baja que el jugador apenas podrá moverse.
*/

enum class tirednessLevel { NONE, TIRED, EXHAUSTED };

class TirednessComponent : public PlayerHealthComponent
{
private:
	float tiredness;
	KeyboardPlayerCtrl* kb;
	tirednessLevel tirednessLev;

public:
	TirednessComponent();
	void init() override;
	void updateLevel(); //Actualiza el nivel de cansacio de jugador en base a su cansancio
	void calculatePlayerSpeed() const ; //Calcula velocidad del jugador en base a su cansancio y la modifica (velocidad del transform)
	 
	void calculateTravelSpeed() const; //Metodo que en base al cansancio, aumente  en un cierto % el tiempo de viaje a las localizaciones (necesita el sistema de localizaciones)

	void sleep(int hours); //Horas descansadas como parametro
	void decreaseTiredness(float tiredness);
	tirednessLevel getTirednessLevel() { return tirednessLev; }
};

