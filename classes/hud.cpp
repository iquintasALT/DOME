#include "hud.h"
#include <string> 
#include "../classes/weapon_behaviour.h"
#include "../classes/charge_weapon.h"
#include"../classes/physiognomy.h"
#include "ricochet_weapon.h"
#include "../ecs/Manager.h"
#include "../components/player_health_component.h"
#include "../components/bleedout_component.h"

#include <iostream>
hud::hud(Manager* m, Transform* initialPos, Player* p) : Entity(m)
{
	posCam = initialPos;
	player = p;

	time = new Countdown(10000); //Hay que pasarle el pos Cam para que se mueva
	timer = &sdlutils().images().at("dclock");

	m->addEntity(this);
	m->addRenderLayer<Interface>(this);

	states = player->getPhysiognomy()->getHealthComponents();

	charger = player->getCurrentWeapon()->getWeaponMovement()->getTamCharger();
}

void hud::update()
{
	time->update();

	bullets = player->getCurrentWeapon()->getWeaponMovement()->getChargerBullets();
	totalBullet = player->getCurrentWeapon()->getWeaponMovement()->getTotalBullets();
	if (totalBullet < 0) totalBullet = 0;
}

void hud::render()
{
	//Arriba derecha
	Vector2D aux = Vector2D(995, 9);
	SDL_Rect dest = build_sdlrect(aux, 75, 35);
	timer->render(dest);

	time->render();

	//Renderizar las balas cargador
	nbullets = new Texture(sdlutils().renderer(), to_string(bullets) + " / " + to_string(charger), sdlutils().fonts().at("OrbitronRegular"),
		build_sdlcolor(0xffffffff));

	nbullets->render(posCam->getPos().getX() - 50, posCam->getPos().getY() + 550);
	delete nbullets;
	nbullets = nullptr;

	//Numero pequeñito
	nbullets = new Texture(sdlutils().renderer(), to_string(totalBullet), sdlutils().fonts().at("Orbitron12"),
		build_sdlcolor(0xffffffff));

	nbullets->render(posCam->getPos().getX(), posCam->getPos().getY() + 570);
	delete nbullets;
	nbullets = nullptr;
	//Renderizar los estados

	/// i es el indice interno del estado. Como el dessangrado es un estado que puede ocupar
	/// varios espacios, necesitamos j para contar el número de espacios
	for (int i = 0, j = 0; 
		i < (player->getPhysiognomy()->getNumStates() + 1 - player->getPhysiognomy()->getNumBleedStates()); 
		i++, j++)
	{
		if (dynamic_cast<BleedoutComponent*>(states->operator[](i)))
		{
			for (; j < player->getPhysiognomy()->getNumBleedStates() - 1; j++)
			{
				drawStatus(i, j, 13);
			}
		}
		drawStatus(i, j, states->operator[](i)->getFrameIndex());
	}
}

void hud::drawStatus(int stateNum, int pos, int frameIndex)
{
	Vector2D aux = Vector2D(16 + pos * 33, 20);
	SDL_Rect dest = build_sdlrect(aux, 33, 33);
	int width = states->operator[](stateNum)->getTexture()->width() / 4;
	int height = states->operator[](stateNum)->getTexture()->height() / 4;
	SDL_Rect src = build_sdlrect((frameIndex % 4) * width, (frameIndex / 4) * height, width, height);
	states->operator[](stateNum)->getTexture()->render(src, dest);
}