#pragma once
#include "player_health_component.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/checkML.h"
class KeyboardPlayerCtrl;
class Player;
class Physiognomy;

/*
* ContusionComponent es un daño que puede recibir el jugador al caer desde una gran altura.
* Es temporal, es decir, el jugador puede decidir esperar que automaticamente desaparecza o curarlo.
* En el tiempo en el que este daño este activo, el jugador no podrá saltar.
*/

class ConcussionComponent : public PlayerHealthComponent
{
private:
	Physiognomy* phys;
	int time;
	KeyboardPlayerCtrl* kb;
public:
	ConcussionComponent() : kb(nullptr), time(0), phys(nullptr) {};
	~ConcussionComponent();
	void init() override;
	void update() override;

	void increaseTime(int time);
	void cancelJump();
	void activateJump();
};

