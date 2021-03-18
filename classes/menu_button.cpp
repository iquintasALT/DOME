#include "menu_button.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../sdlutils/InputHandler.h"

MenuButton::MenuButton(Vector2D pos, Texture* t, CallBackOnClick* function, Game* g, Manager* mngr_) 
	: GameObject(mngr_) {
	position = pos;
	size = Vector2D(sdlutils().width() / 5, sdlutils().height() / 5);
	tex = t;
	game = g;
	cbOnClick = function;
	addComponent<Transform>(position, Vector2D(0, 0), size.getX(), size.getY(), 0);
	addComponent<Image>(tex);
}

void MenuButton::update() {
	if (ih().getMouseButtonState(InputHandler::LEFT)){
		Vector2D mousePos(ih().getMousePos().first, ih().getMousePos().second);
		mousePos = Camera::mainCamera->PointToWorldSpace(mousePos);
		 
		if (mousePos.getX() >= position.getX() && mousePos.getY() >= position.getY() &&
		mousePos.getX() <= position.getX() + size.getX() && mousePos.getY() <= position.getY() + size.getY()) {
			cbOnClick(game);
		}
	}
}