#include "hud.h"
#include <string> 
#include "../classes/weapon_behaviour.h"
#include "../classes/charge_weapon.h"
#include"../classes/physiognomy.h"
#include "ricochet_weapon.h"
#include "../ecs/Manager.h"
#include "../components/player_health_component.h"

#include <iostream>
hud::hud(Manager* m, Transform* initialPos, Player* p) : Entity(m)
{
	posCam = initialPos;
	player = p;

	time = new Countdown(10000); //Hay que pasarle el pos Cam para que se mueva

	m->addEntity(this);
	m->addRenderLayer<Interface>(this);

	states = player->getPhysiognomy()->getHealthComponents();
}

void hud::update()
{
	time->update();

	bullets = player->getCurrentWeapon()->getWeaponMovement()->getChargerBullets();

}

void hud::render()
{
	//Arriba derecha
	time->render();

	//Renderizar las balas
	nbullets = new Texture(sdlutils().renderer(), to_string(bullets), sdlutils().fonts().at("OrbitronRegular"),
		build_sdlcolor(0xffffffff));

	nbullets->render(posCam->getPos().getX() + 50, posCam->getPos().getY() + 500);
	delete nbullets;
	nbullets = nullptr;

	//Renderizar los estados

	for (int i = 0; i < player->getPhysiognomy()->getNumStates(); i++)
	{
		Vector2D aux = Vector2D(16 + i * 33, 20);
		SDL_Rect dest = build_sdlrect(aux, 33, 33);

		states->operator[](i)->getTexture()->render(dest);
	}
}