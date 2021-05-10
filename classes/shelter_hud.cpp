#include "shelter_hud.h"
#include "../ecs/Manager.h"
#include "../classes/player.h"
#include "../components/hunger_component.h"
#include "../components/tiredness_component.h"
#include "../sdlutils/SDLUtils.h"
#include "../game/constant_variables.h"

ShelterHud::ShelterHud(Manager* mngr) : Entity(mngr) {
	mngr->addEntity(this);
	mngr->addRenderLayer<Interface>(this);

	player = static_cast<Player*>(mngr->getHandler<Player_hdlr>());
	hunger = player->getComponent<HungerComponent>();
	tiredness = player->getComponent<TirednessComponent>();

	hungerState = tirednessState = &sdlutils().images().at("shelterStatusEffects");
	clock = &sdlutils().images().at("clock");

	assert(hunger != nullptr && tiredness != nullptr);
}

void ShelterHud::render() {
	//Hunger
	SDL_Rect dest = { consts::STATUS_EFFECTS_SIZEX/2, 20, consts::STATUS_EFFECTS_SIZEX, consts::STATUS_EFFECTS_SIZEY };
	SDL_Rect src = { (32 * (int) hunger->getHungerLevel()), 0, 32, 32};
	hungerState->render(src, dest);

	//Tiredness
	dest.x += consts::STATUS_EFFECTS_SIZEX; src.y = 32; src.x = 32 * (int)tiredness->getTirednessLevel();
	tirednessState->render(src, dest);

	//Acciones
	int acciones = 4; //Numero de acciones para probar
	SDL_Rect accDest = { consts::WINDOW_WIDTH - clock->width() / 2 * acciones, dest.y, dest.w, dest.h };
	SDL_Rect accSrc = { 0,0, 64, 64 };

	for (int i = 0; i < acciones; i++) {
		clock->render(accSrc, accDest);
		accDest.x += accSrc.w;
	}
}
