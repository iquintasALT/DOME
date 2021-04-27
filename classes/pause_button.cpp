#include "pause_button.h"
#include "../sdlutils/InputHandler.h"
#include "../components/Image.h"
#include "../sdlutils/SDLUtils.h"

PauseButton::PauseButton(Vector2D pos, Vector2D size, Texture* t, CallBackOnClick* function, Game* g, Manager* mngr_) : MenuButton(pos, size, t, function, g, mngr_) {
	img = getComponent<Image>();
	over = false;
	SDL_Rect rect = { 0, 0, size.getX(),size.getY() };
	img->setSrc(rect);
}

void PauseButton::update() {
	
	Vector2D mousePos(ih().getMousePos().first, ih().getMousePos().second);
	if (mousePos.getX() >= position.getX() && mousePos.getY() >= position.getY() &&
		mousePos.getX() <= position.getX() + size.getX() && mousePos.getY() <= position.getY() + size.getY()) {
		if (!over) {
			over = true;
			img->changeFrame(1, 0);
		}
	}
	else {
		if (over) {
			over = false;
			img->changeFrame(0, 0);
		}
	}
	if (ih().getMouseButtonState(InputHandler::LEFT)) {
		if (over) {
			img->changeFrame(2, 0);
			cbOnClick(game);
		}
	}
}
