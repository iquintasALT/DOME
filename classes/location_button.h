#pragma once
#include "menu_button.h"

using CallBackOnClickLocation = void(Game* g, int index);

class LocationButton : public MenuButton
{
private:
	int index;
	CallBackOnClickLocation* cb;

public:
	LocationButton(Vector2D pos, Texture* t, Game* g, Manager* mngr_, int number);
	void update() override;
	int getIndex() { return index; }
};
