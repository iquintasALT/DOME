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
	Texture* name;
	bool clicked;
public:
	PauseButton(Vector2D pos, Vector2D size, Texture* t, CallBackOnClick* function, Game* g, Manager* mngr_, int type = 0, std::string buttonName = " ", Uint8 alpha = 255);
	~PauseButton();
	void update() override;
	void render() override;
};


class MainMenuButton : public PauseButton {
public:
	MainMenuButton(Vector2D pos, Vector2D size, Texture* t, CallBackOnClick* function, Game* g, Manager* mngr_, int type = 0, std::string buttonName = " ", Uint8 alpha = 255);
	void render() override;
};