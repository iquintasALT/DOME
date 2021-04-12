#pragma once
#include "menu_button.h"

using CallBackOnClickLocation = void(Game* g, int index);

class LocationButton : public MenuButton
{
private:
	int index;
	CallBackOnClickLocation* cb;
protected:
	static int INDEX;
public:
	LocationButton(Vector2D pos, Texture* t, CallBackOnClickLocation* function, Game* g, Manager* mngr_);
	void update() override;
	int getIndex() { return index; }
};
