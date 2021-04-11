#include "hud.h"
#include <string> 

hud::hud(Transform* initialPos, Player* p)
{
	posCam = initialPos;
	player = p;

	time = new Countdown(1000); //Hay que pasarle el pos Cam para que se mueva
}

void hud::init()
{

}

void hud::update()
{
	time->update();

	//bullets = player->getCurrentWeapon()->GetWeaponMOvement()->GetBullets(); //No hay todavia
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
}