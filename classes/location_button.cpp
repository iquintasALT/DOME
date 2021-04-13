#include "../classes/location_button.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../sdlutils/InputHandler.h"

LocationButton::LocationButton(Vector2D pos, Texture* t, Game* g, Manager* mngr_, int number) : MenuButton(pos, t, nullptr, g, mngr_) {
	index = number;
	cb = nullptr;
}

void LocationButton::update() {
	if (ih().getMouseButtonState(InputHandler::LEFT)) {
		Vector2D mousePos(ih().getMousePos().first, ih().getMousePos().second);
		mousePos = Camera::mainCamera->PointToWorldSpace(mousePos);

		if (mousePos.getX() >= position.getX() && mousePos.getY() >= position.getY() &&
			mousePos.getX() <= position.getX() + size.getX() && mousePos.getY() <= position.getY() + size.getY()) {
			//cb(game, index);
		}
	}
}
