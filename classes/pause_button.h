#pragma once
#include "../classes/menu_button.h"
class Image;
enum ButtonType {NONETYPE, VOLUME};
class PauseButton : public MenuButton
{
protected:
	Image* img;
	bool over;
	int type_;
public:
	PauseButton(Vector2D pos, Vector2D size, Texture* t, CallBackOnClick* function, Game* g, Manager* mngr_, int type = 0);
	void update() override;
};