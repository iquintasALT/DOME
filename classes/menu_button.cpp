#include "menu_button.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../sdlutils/InputHandler.h"

MenuButton::MenuButton(Vector2D pos, Vector2D size_, Texture* t, CallBackOnClick* function, Game* g, Manager* mngr_)
	: GameObject(mngr_) {
	position = pos;
	size = size_;
	tex = t;
	game = g;
	cbOnClick = function;
	addComponent<Transform>(position, size.getX(), size.getY(), 0);
	addComponent<Image>(tex, 1, 1, 0, 0, true);
	mngr_->addRenderLayer<Interface>(this);
}

void MenuButton::update() {
	if (ih().getMouseButtonState(InputHandler::LEFT)){
		Vector2D mousePos(ih().getMousePos().first, ih().getMousePos().second);
		 
		if (mousePos.getX() >= position.getX() && mousePos.getY() >= position.getY() &&
		mousePos.getX() <= position.getX() + size.getX() && mousePos.getY() <= position.getY() + size.getY()) {
			cbOnClick(getMngr());
		}
	}
}