#include "workshop.h"

Workshop::Workshop(Manager* mngr_) : GameEntity(mngr_) {
	mngr_->addEntity(this);
	renderFlag = false;

	bg_size = { 930, 630 };
	bg_pos = Vector2D(sdlutils().width() / 2 - bg_size.getX() / 2, sdlutils().height() / 2 - bg_size.getY() / 2);
	bButton_size = { 65,64 };
	bButton_pos = Vector2D(bg_pos.getX() - bButton_size.getX() / 2, bg_pos.getY() - bButton_size.getY() / 2);
	tr = addComponent<Transform>(bg_pos, Vector2D(), 930, 630, 0);

	bgName = "craft_bg";
	bButtonName = "craft_back_button";

	renderImg = nullptr;
}

void Workshop::setRenderFlag(bool set) {
	renderFlag = set;
}

void Workshop::setImg(Vector2D pos, Vector2D size, std::string name) {
	tr->setPos(pos);
	tr->setW(size.getX());
	tr->setH(size.getY());
	removeComponent<Image>();
	renderImg = addComponent<Image>(&sdlutils().images().at(name));
}

void Workshop::update() {
	if (renderFlag) {
		Vector2D mousePos(ih().getMousePos().first, ih().getMousePos().second);
		if (ih().getMouseButtonState(InputHandler::LEFT) && Collisions::collides(mousePos, 1, 1, bButton_pos, bButton_size.getX(), bButton_size.getY())) {
			renderFlag = false;
		}
	}
}

void Workshop::render() {
	if (renderFlag) {
		setImg(bg_pos, bg_size, bgName);
		renderImg->render();

		setImg(bButton_pos, bButton_size, bButtonName);
		renderImg->render();
	}
}