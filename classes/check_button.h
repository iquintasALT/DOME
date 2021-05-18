#pragma once
#include "menu_button.h"
class Texture;

class CheckButton : public MenuButton
{
private:
	bool over, checked, clicked;
	Image* img;
public:
	CheckButton(Vector2D pos, Vector2D size, Texture* t, CallBackOnClick* function, Game* g, Manager* mngr_);
	void update() override;
	void render() override;
};

