#include "menu_button.h"

MenuButton::MenuButton(Vector2D pos, Texture* t, CallBackOnClick* function, Game* g, Manager* mngr_) 
	: GameObject(mngr_) {
	position = pos;
	tex = t;
	game = g;
	size = Vector2D(sdlutils().width() / 5, sdlutils().height() / 5);
	cbOnClick = function;
}

void MenuButton::render() const {
	SDL_Rect dest = build_sdlrect(position.getX(), position.getY(), size.getX(), size.getY());
	tex->render(dest);
}

bool MenuButton::handleEvents(const SDL_Event& e) {
	/*if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT) {
		SDL_Point p = { e.button.x, e.button.y };
		const SDL_Rect* dest = &build_sdlrect(position.getX(), position.getY(), size.getX(), size.getY());
		if (SDL_PointInRect(&p, dest) == SDL_TRUE) {
			cbOnClick(game);
			return true;
		}
	}*/
	return false;
}