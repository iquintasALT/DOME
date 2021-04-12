#include "hud.h"
#include <string> 
#include "../classes/weapon_behaviour.h"
#include "../classes/charge_weapon.h"
#include "ricochet_weapon.h"
#include "../ecs/Manager.h"

hud::hud(Manager* m, Transform* initialPos, Player* p) : Entity(m)
{
	posCam = initialPos;
	player = p;

	time = new Countdown(1000); //Hay que pasarle el pos Cam para que se mueva

	state1 = &sdlutils().images().at("player");
	state2 = &sdlutils().images().at("player");

	m->addEntity(this);
}

void hud::init()
{

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

	nbullets = new Texture(sdlutils().renderer(), to_string(bullets), sdlutils().fonts().at("ARIAL24"),
		build_sdlcolor(0xffffffff));

	nbullets->render(posCam->getPos().getX() + 50, posCam->getPos().getY() + 500);
	delete nbullets;
	nbullets = nullptr;

	//Renderizar los estados

	Vector2D aux = Vector2D(10 + 35 , 10);
	SDL_Rect dest = build_sdlrect(aux, 33, 33);
	state1->render(dest);

	aux = Vector2D(10 + 70, 10);
	dest = build_sdlrect(aux, 33, 33);
	state2->render(dest);
}