#pragma once
#include "../classes/menu_button.h"
class Image;

class PauseButton : public MenuButton
{
protected:
	Image* img;
	bool over;
public:
	PauseButton(Vector2D pos, Vector2D size, Texture* t, CallBackOnClick* function, Game* g, Manager* mngr_);
	void update() override;
};