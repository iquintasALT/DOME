#pragma once
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/checkML.h"
#include <vector>

class Manager;
class HungerComponent;
class TirednessComponent;
class Player;
class Texture;
class ShelterScene;
class TextWithBackground;

class ShelterHud : public Entity
{
private:
	struct _tooltip_ {
		Transform* t;
		TextWithBackground* text;
	};
	HungerComponent* hunger;
	TirednessComponent* tiredness;
	Player* player;
	ShelterScene* shelter;

	Texture* hungerState;
	Texture* tirednessState;
	Texture* clock;

	TextWithBackground* tooltipText;
	std::vector<_tooltip_> tooltipTextures;
	Transform* tooltipTr;

public:
	ShelterHud(Manager* mngr, ShelterScene* shelter);
	void render() override;
	void drawTooltip(int indice, SDL_Rect dest);
	void manageToolTips();
};