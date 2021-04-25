#include "sleep_station.h"

SleepStation::SleepStation(Manager* realMngr_, Manager* mngr_) : GameEntity(mngr_) {
	realMngr_->addEntity(this);
	realMngr_->addRenderLayer<Interface>(this);

	renderFlag = false;
	mouseClick = false;

	playerTr = realMngr_->getHandler<Player_hdlr>()->getComponent<Transform>();

	//INICIALIZACION IMAGENES DEL FONDO, FLECHAS Y X PARA SALIR
	bg = mngr_->addEntity();
	bButton = mngr_->addEntity();
	leftButton = mngr_->addEntity();
	rightButton = mngr_->addEntity();
	clock = mngr_->addEntity();
	arrow = mngr_->addEntity();
	sleepButton = mngr_->addEntity();

	Vector2D bg_size = { 930, 630 };
	Vector2D bg_pos = Vector2D(sdlutils().width() / 2 - bg_size.getX() / 2, sdlutils().height() / 2 - bg_size.getY() / 2);
	Vector2D bButton_size = { 65,64 };
	Vector2D bButton_pos = Vector2D(bg_pos.getX() - bButton_size.getX() / 2, bg_pos.getY() - bButton_size.getY() / 2);

	setImg(bg, bg_pos, bg_size, "craft_bg");
	setImg(bButton, bButton_pos, bButton_size, "craft_back_button");

	bg_tr = bg->getComponent<Transform>();
	bButton_tr = bButton->getComponent<Transform>();

	Vector2D arrows_size = { 170,70 };
	Vector2D arrowLeft_pos = { bg_pos.getX() + bg_tr->getW() / 2 - bg_tr->getW() / 4 - arrows_size.getX() / 2,bg_pos.getY() + bg_size.getY() / 2 };
	Vector2D arrowRight_pos = { bg_pos.getX() + bg_tr->getW() / 2 + bg_tr->getW() / 4 - arrows_size.getX() / 2,bg_pos.getY() + bg_size.getY() / 2 };

	setImg(leftButton, arrowLeft_pos, arrows_size, "craft_arrow");
	setImg(rightButton, arrowRight_pos, arrows_size, "craft_arrow");
	leftButton_tr = leftButton->getComponent<Transform>();
	leftButton_tr->setRot(90.0);
	rightButton_tr = rightButton->getComponent<Transform>();
	rightButton_tr->setRot(90.0);
	leftButton->getComponent<Image>()->setFlip(SDL_FLIP_HORIZONTAL);

	Vector2D clock_size = { 200, 200 };
	Vector2D clock_pos = { bg_pos.getX() + bg_tr->getW() / 2 - clock_size.getX() / 2, bg_pos.getY() + bg_tr->getH() / 2 - clock_size.getY() / 2 };
	clock->addComponent<Transform>(clock_pos, clock_size.getX(), clock_size.getY(), 0);
	clock->addComponent<Image>(&sdlutils().images().at("clock"), 1, 2, 0, 0, true);
	arrow_tr = arrow->addComponent <Transform>(clock_pos, clock_size.getX(), clock_size.getY(), 0);
	arrow->addComponent<Image>(&sdlutils().images().at("clock"), 1, 2, 0, 1, true);

	Vector2D sleepButton_size = { 265,105 };
	Vector2D sleepButton_pos = { bg_pos.getX() + bg_tr->getW() / 2 - sleepButton_size.getX() / 2,
		bg_pos.getY() + clock_pos.getY() + bg_tr->getH() / 3 - sleepButton_size.getY() / 2 };
	setImg(sleepButton, sleepButton_pos, sleepButton_size, "craft_slot_box");
}

void SleepStation::init() {
	/*playerInv = getMngr()->getHandler<Player_hdlr>()->getComponent<Inventory>();*/
}

void SleepStation::setRenderFlag(bool set) {
	renderFlag = set;
	if (set)
		playerTr->getEntity()->setActive(false);
}

void SleepStation::setImg(Entity* entity, Vector2D pos, Vector2D size, std::string name) {
	entity->addComponent<Transform>(pos, size.getX(), size.getY(), 0);
	entity->addComponent<Image>(&sdlutils().images().at(name), 1, 1, 0, 0, true);
}

void SleepStation::update() {
	Entity::update();
	getMngr()->refresh();

	if (renderFlag) {
		Vector2D mousePos(ih().getMousePos().first, ih().getMousePos().second);
		if (ih().getMouseButtonState(InputHandler::LEFT) && !mouseClick) {
			mouseClick = true;

			if (Collisions::collides(mousePos, 1, 1, bButton_tr->getPos(), bButton_tr->getW(), bButton_tr->getH())) {
				renderFlag = false;
				playerTr->getEntity()->setActive(true);
			}
			else if (Collisions::collides(mousePos, 1, 1, leftButton_tr->getPos(), leftButton_tr->getW(),
				leftButton_tr->getH())) {
				//rotar flecha
				std::cout << "rotar izq" << endl;
				arrow_tr->setRot(arrow_tr->getRot() - 45);
			}
			else if (Collisions::collides(mousePos, 1, 1, rightButton_tr->getPos(), rightButton_tr->getW(),
				rightButton_tr->getH())) {
				//rotar flecha
				std::cout << "rotar der" << endl;
				arrow_tr->setRot(arrow_tr->getRot() + 45);
			}
		}
		else if (!ih().getMouseButtonState(InputHandler::LEFT)) { mouseClick = false; }
	}
}

void SleepStation::render() {
	Entity::render();
	getMngr()->refresh();
	if (renderFlag) {
		bg->render();
		bButton->render();

		leftButton->render();
		rightButton->render();
		clock->render();
		arrow->render();
		sleepButton->render();
	}
}

void SleepStation::renderImg(float posX, float posY, int row, int col, int sizeX, int sizeY) {
	Entity* aux = getMngr()->addEntity();
	aux->addComponent<Transform>(Vector2D{ posX,posY }, sizeX, sizeY, 0);
	aux->addComponent<Image>(&sdlutils().images().at("items"), 4, 3, row, col, true)->render();
	aux->setActive(false);
}
