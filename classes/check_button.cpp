#include "check_button.h"
#include "../sdlutils/InputHandler.h"
#include "../components/Image.h"
#include "../game/Game.h"

CheckButton::CheckButton(Vector2D pos, Vector2D size, Texture* t, CallBackOnClick* function, Game* g, Manager* mngr_) 
	: MenuButton(pos, size, t, function, g, mngr_), over(false), img(nullptr), checked(false), clicked(false){
	img = getComponent<Image>();
	SDL_Rect rect = { 0, 0, t->width() / 3, t->height() };
	img->setSrc(rect);

	if (g->getFPSActive()) {
		img->changeFrame(2, 0);
		checked = true;
	}
	else {
		img->changeFrame(0, 0);
		checked = false;
	}
}

void CheckButton::update() {
	Vector2D mousePos(ih().getMousePos().first, ih().getMousePos().second);

	if (mousePos.getX() >= position.getX() && mousePos.getY() >= position.getY() &&
		mousePos.getX() <= position.getX() + size.getX() && mousePos.getY() <= position.getY() + size.getY()) {
		if (!over) {
			soundManager().playSFX("over_button");
			over = true;
			if(!checked) img->changeFrame(1, 0);
		}
	}
	else if (over) {
		over = false;
		if (!checked) img->changeFrame(0, 0);
	}

	if (over) {
		if (ih().getMouseButtonState(InputHandler::LEFT)) {
			if (!clicked) {
				clicked = true;
				soundManager().playSFX("push_button");
				checked = !checked;
				cbOnClick(getMngr());
				if (checked) img->changeFrame(2, 0);
				else img->changeFrame(1, 0);
			}
		}
		else clicked = false;
	}
	
}

void CheckButton::render() {
	img->render();
}
