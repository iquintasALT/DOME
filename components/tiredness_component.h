#pragma once
#include "player_health_component.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "../game/checkML.h"
#include "../utils/Vector2D.h"
#include "../components/Transform.h"
#include "../components/KeyboardPlayerCtrl.h"
#include <list>

/*
* TirednessComponent es un componente para el jugador que mide su nivel de cansacio.
* Afecta a su velocidad de movimiento y cuanto menos duerma el jugador, el nivel 
* de cansancio del jugador aumentará y subira de nivel, habiendo tres niveles
* (Apenas cansado, cansado y exhausto).
* Si está exhasuto la velocidad de movimiento es tan baja que el jugador apenas podrá moverse.
*/
const int MAX_SLEEP_HOURS = 8; //Horas máximas de sueño en una noche
const int PREVIOUS_DAYS = 3; //Dias previos para calcular las horas

const float NONETIRED_LEVEL = 0.75f; //Por encinma del 75% estará en NONE y por debajo en TIRED
const float TIRED_LEVEL = 0.35f; //Por encima del 35% estará en TIRED y por debajo en EXHASUTED

enum class tirednessLevel { NONE, TIRED, EXHAUSTED };

class TirednessComponent : public PlayerHealthComponent
{
public:
	TirednessComponent() : tiredness(1.0f), tirednessLevel(tirednessLevel::NONE), kb(nullptr){};
	void init() override;
	void updateLevel(); //Actualiza el nivel de cansacio de jugador en base a su cansancio
	void calculatePlayerSpeed(); //Calcula velocidad del jugador en base a su cansancio y la modifica (velocidad del transform)
	 
	//void calculateTravelSpeed(); //Metodo que en base al cansancio, aumente  en un cierto % el tiempo de viaje a las localizaciones (necesita el sistema de localizaciones)

	void calculateTiredness(); //Metodo que se llama al principio de cada para calcular el cansancio del jugador en base a las horas dormidas durante los ultimos dias
	void sleep(int hours); //Horas descansadas como parametro

	void setTiredness(float a) { tiredness = a; }
private:
	float tiredness;
	KeyboardPlayerCtrl* kb;
	tirednessLevel tirednessLevel;
	list<int> sleepLog;
};

