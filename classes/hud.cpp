#include "hud.h"
#include <string> 
#include "../classes/weapon_behaviour.h"
#include "../classes/charge_weapon.h"
#include"../classes/physiognomy.h"
#include "ricochet_weapon.h"
#include "../ecs/Manager.h"
#include "../components/player_health_component.h"
#include "../components/bleedout_component.h"
#include "../components/TextWithBackGround.h"

#include <iostream>
#include <string>
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

	//TextWithBackground(std::string str, Font & font, SDL_Color  color, Texture * texture, bool appearingText = false, float appeatingTextSpeed = 1, bool alignInCenter = false);
	
	tooltip = m->addEntity();
	tooltip->addComponent<Transform>(Vector2D(), 200, 10);
	//tooltipText = tooltip->addComponent<TextWithBackground>();
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
	if (states->size() > 0)
	{
		/// Empezamos desde el final de la lista, sabiendo que los desangrados estarán al final
		/// Además, si hay algún desangrado, el primero que dibujaremos será el incompleto

		list<PlayerHealthComponent*>::iterator i = states->end();
		--i;

		int n = player->getPhysiognomy()->getNumStates() - 1; // el indice de recorrido como entero

		// Dibujamos el desangrado incompleto, si hay
		if (player->getPhysiognomy()->getNumBleedStates() > 0)
		{
			drawStatus(n, (*i)->getFrameIndex());
			--i; --n;
		}

		// Dibujamos los desangrados completos, si hay
		while (n >= player->getPhysiognomy()->getNumStates() - player->getPhysiognomy()->getNumBleedStates())
		{
			drawStatus(n, 13);
			if (i != states->begin()) --i; --n;
		}

		// Dibujamos el resto de estados
		if (n >= 0)
			do
			{
				drawStatus(n, (*i)->getFrameIndex());
				if (i != states->begin()) --i;
				--n;
			} while (i != states->begin());
	}
}

void hud::drawStatus(int pos, int frameIndex)
{
	// Si no hay estados que dibujar, no deberíamos estar en este método
	assert(states->size() > 0);

	Vector2D aux = Vector2D(16 + pos * 33, 20);
	SDL_Rect dest = build_sdlrect(aux, 33, 33);
	int width = 32;
	int height = 32;
	SDL_Rect src = build_sdlrect((frameIndex % 4) * width, (frameIndex / 4) * height, width, height);
	states->front()->getTexture()->render(src, dest);
}