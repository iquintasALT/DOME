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
#include "../components/Image.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../game/Game.h"
#include "../game/constant_variables.h"
#include <iostream>
#include <string>

hud::hud(Manager* m, Transform* initialPos, Player* p, Countdown* time_) : Entity(m)
{
	posCam = initialPos;
	player = p;

	time = time_;//Hay que pasarle el pos Cam para que se mueva
	timer = &sdlutils().images().at("dclock");
	marco = &sdlutils().images().at("marco");
	m->addEntity(this);
	m->addRenderLayer<Interface>(this);

	states = player->getPhysiognomy()->getHealthComponents();

	numberOfWounds = states->size();

	//TextWithBackground(std::string str, Font & font, SDL_Color  color, Texture * texture, bool appearingText = false, float appeatingTextSpeed = 1, bool alignInCenter = false);
	
	Entity* tooltip = m->addEntity();
	tooltipTr = tooltip->addComponent<Transform>(Vector2D(), 400, 10);
	tooltipText = tooltip->addComponent<TextWithBackground>("Inventario",
		sdlutils().fonts().at("Orbitron32"), build_sdlcolor(0xffffffff), &sdlutils().images().at("tooltipBox"));
	tooltip->setActive(false);

	Entity* arma = m->addEntity();
	arma->addComponent<Transform>(Vector2D(7, consts::WINDOW_HEIGHT - 75 - 7), 75, 75);
	currentWeapon = arma->addComponent<Image>(&sdlutils().images().at("weaponHUD"), 3, 3, 0, 0, true);
	m->addRenderLayer<Interface>(arma);

	createStatesBackgrounds();

	woundDescriptions = std::vector<std::string>{
		{"You are INTOXICATED, you are getting hungry..."},
		{"You suffered a CONTUSSION, now, you can't jump..."},
		{"You feel a lot of PAIN, you can`t aim well..."},
		{"You are FREEZING, leave now!"},
		{"You are BLEEDING"}, 
		{"You have a serious wound..."}
	};
}

void hud::chooseWeapon(int type, int tier)
{
	currentWeapon->changeFrame(tier, type);
}

void hud::createStatesBackgrounds() {
	stateBackground = &sdlutils().images().at("statesBackground");
	stateBackground->setAlpha(100);
	stateBackgroundRed = &sdlutils().images().at("statesBackgroundRed");
	stateBackgroundRed->setAlpha(100);
}

void hud::update()
{
	time->update();

	bullets = player->getWeapon()->getCurrentWeapon()->getBulletsInMagazine();
	totalBullet = player->getWeapon()->getCurrentWeapon()->getAmmoReserves();
	if (totalBullet < 0) totalBullet = 0;

	int type = (int)player->getWeapon()->typeOfWeapon();
	int tier = player->getWeapon()->tierOfWeapon();

	chooseWeapon(type, tier);

	magSize = player->getWeapon()->getCurrentWeapon()->getMagazineSize();

	if (!time->keepPlaying() && !frozen)
	{
		player->getPhysiognomy()->addHypothermiaState();
		frozen = true;
	}
}

void hud::render() {
	Vector2D mouse = Vector2D(ih().getMousePos().first, ih().getMousePos().second);

	//Arriba derecha
	Vector2D aux = Vector2D(consts::WINDOW_WIDTH - 80, 10);
	SDL_Rect dest = build_sdlrect(aux, 75, 35);
	timer->render(dest);

	time->render();

	aux = Vector2D(-1, consts::WINDOW_HEIGHT - 100);
	dest = build_sdlrect(aux, 155, 95);
	marco->render(dest);

	//Renderizar las balas cargador
	nbullets = new Texture(sdlutils().renderer(), to_string(bullets) + " / " + to_string(magSize), sdlutils().fonts().at("Orbitron12"),
		build_sdlcolor(0xffffffff));

	nbullets->render(100, consts::WINDOW_HEIGHT - 86);
	delete nbullets;
	nbullets = nullptr;

	//Numero peque�ito
	nbullets = new Texture(sdlutils().renderer(), to_string(totalBullet), sdlutils().fonts().at("OrbitronRegular"),
		build_sdlcolor(0xffffffff));

	nbullets->render(103, consts::WINDOW_HEIGHT - 56);
	delete nbullets;
	nbullets = nullptr;

	//Renderizar los fondos de los estados
	SDL_Rect destRect = { consts::STATUS_EFFECTS_SIZEX / 2, 30, consts::STATUS_EFFECTS_SIZEX, consts::STATUS_EFFECTS_SIZEY };
	for (int i = 0; i < consts::MAX_MULTIPLE_STATES -1; i++) {
		stateBackground->render(destRect);
		destRect.x += destRect.w;
	}
	stateBackgroundRed->render(destRect);

	//Renderizar los estados
	if (states->size() > 0)
	{
		if (states->size() != numberOfWounds) {
			numberOfWounds = states->size();
			for (int i = 0; i < tooltipTextures.size(); i++) {
				tooltipTextures[i].t->getEntity()->setDead(true);
			}
			tooltipTextures.clear();

			tooltipTextures.reserve(numberOfWounds);
			for (int i = 0; i < numberOfWounds; i++) {
				Entity* ent = mngr_->addEntity();
				Transform* t = ent->addComponent<Transform>(Vector2D(), 400, 10);
				TextWithBackground* text = ent->addComponent<TextWithBackground>(" ",
					sdlutils().fonts().at("Orbitron24"), build_sdlcolor(0xffffffff), &sdlutils().images().at("tooltipBox"));
				tooltipTextures.push_back({t, text});
				ent->setActive(false);
			}
		}

		/// Empezamos desde el final de la lista, sabiendo que los desangrados estar�n al final
		/// Adem�s, si hay alg�n desangrado, el primero que dibujaremos ser� el incompleto

		list<PlayerHealthComponent*>::iterator i = states->end();
		--i;

		int n = player->getPhysiognomy()->getNumStates() - 1; // el indice de recorrido como entero

		// Dibujamos el desangrado incompleto, si hay
		if (player->getPhysiognomy()->getNumBleedStates() > 0)
		{
			drawStatus(n, (*i)->getFrameIndex(), mouse);
			if(i != states->begin()) --i; 
			--n;
		}

		// Dibujamos los desangrados completos, si hay
		while (n >= player->getPhysiognomy()->getNumStates() - player->getPhysiognomy()->getNumBleedStates())
		{
			drawStatus(n, 13, mouse);
			if (i != states->begin()) --i; --n;
		}

		// Dibujamos el resto de estados
		if (n >= 0)
			do
			{
				drawStatus(n, (*i)->getFrameIndex(), mouse);
				if (i != states->begin()) --i;
				--n;
			} while (n >= 0);
	}
}

void hud::drawStatus(int pos, int frameIndex, Vector2D mouse) {
	// Si no hay estados que dibujar, no deberiamos estar en este metodo
	assert(states->size() > 0);

	Vector2D aux = Vector2D(consts::STATUS_EFFECTS_SIZEX/2 + pos * consts::STATUS_EFFECTS_SIZEX, 30);
	SDL_Rect dest = build_sdlrect(aux, consts::STATUS_EFFECTS_SIZEX, consts::STATUS_EFFECTS_SIZEY);
	SDL_Rect src = build_sdlrect((frameIndex % 4) * 32, (frameIndex / 4) * 32, 32, 32);
	states->front()->getTexture()->render(src, dest);

	if (mouse.getX() > dest.x && mouse.getX() < dest.x + dest.w &&
		mouse.getY() > dest.y && mouse.getY() < dest.y + dest.h) {
		
		int n = pos;
		tooltipTextures[n].t->setPos(mouse);

		if (frameIndex > 3) {
			if (frameIndex == 13) tooltipTextures[n].text->changeText(woundDescriptions[woundDescriptions.size() - 1]);
			else  tooltipTextures[n].text->changeText(woundDescriptions[4]);
		}
		else tooltipTextures[n].text->changeText(woundDescriptions[frameIndex]);

		tooltipTextures[n].text->render();
		
	}
}