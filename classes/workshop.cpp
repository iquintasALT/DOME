#include "workshop.h"

Workshop::Workshop(Manager* mngr_) : GameEntity(mngr_) {
	mngr_->addEntity(this);
	renderFlag = false;

	bg = mngr_->addEntity();
	bButton = mngr_->addEntity();

	Vector2D bg_size = { 930, 630 };
	Vector2D bg_pos = Vector2D(sdlutils().width() / 2 - bg_size.getX() / 2, sdlutils().height() / 2 - bg_size.getY() / 2);
	Vector2D bButton_size = { 65,64 };
	Vector2D bButton_pos = Vector2D(bg_pos.getX() - bButton_size.getX() / 2, bg_pos.getY() - bButton_size.getY() / 2);

	setImg(bg, bg_pos, bg_size, "craft_bg");
	setImg(bButton, bButton_pos, bButton_size, "craft_back_button");
	bg_tr = bg->getComponent<Transform>();
	bButton_tr = bButton->getComponent<Transform>();
}


void Workshop::setRenderFlag(bool set) {
	renderFlag = set;
}

void Workshop::setImg(Entity* entity, Vector2D pos, Vector2D size, std::string name) {
	entity->addComponent<Transform>(pos, Vector2D(), size.getX(), size.getY(), 0);
	entity->addComponent<Image>(&sdlutils().images().at(name));
}

void Workshop::update() {
	if (renderFlag) {
		Vector2D mousePos(ih().getMousePos().first, ih().getMousePos().second);
		if (ih().getMouseButtonState(InputHandler::LEFT) && Collisions::collides(mousePos, 1, 1, bButton_tr->getPos(), bButton_tr->getW(), bButton_tr->getH())) {
			renderFlag = false;
		}
	}
}

void Workshop::render() {
	if (renderFlag) {
		bg->render();
		bButton->render();
	}
}