#include "workshop.h"

Workshop::Workshop(Manager* mngr_, CraftingSystem* cs) : GameEntity(mngr_) {
	craftSys = cs;
	mngr_->addEntity(this);
	renderFlag = false;
	listIndex = 0;
	mouseClick = false;

	renderRightWindow = false;
	rightWindowIndex = 0;

	//INICIALIZACION IMAGENES DEL FONDO, FLECHAS Y X PARA SALIR
	bg = mngr_->addEntity();
	bButton = mngr_->addEntity();
	arrowUp = mngr_->addEntity();
	arrowDown = mngr_->addEntity();
	craftButton = mngr_->addEntity();

	Vector2D bg_size = { 930, 630 };
	Vector2D bg_pos = Vector2D(sdlutils().width() / 2 - bg_size.getX() / 2, sdlutils().height() / 2 - bg_size.getY() / 2);
	Vector2D bButton_size = { 65,64 };
	Vector2D bButton_pos = Vector2D(bg_pos.getX() - bButton_size.getX() / 2, bg_pos.getY() - bButton_size.getY() / 2);

	setImg(bg, bg_pos, bg_size, "craft_bg");
	setImg(bButton, bButton_pos, bButton_size, "craft_back_button");
	bg_tr = bg->getComponent<Transform>();
	bButton_tr = bButton->getComponent<Transform>();

	Vector2D arrows_size = { 170,70 };
	Vector2D arrowUp_pos = { bg_pos.getX() + bg_tr->getW() / 4 - arrows_size.getX() / 2,bg_pos.getY() - arrows_size.getY() / 2 };
	Vector2D arrowDown_pos = { bg_pos.getX() + bg_tr->getW() / 4 - arrows_size.getX() / 2,bg_pos.getY() + bg_tr->getH() - arrows_size.getY() / 2 };

	setImg(arrowUp, arrowUp_pos, arrows_size, "craft_arrow");
	setImg(arrowDown, arrowDown_pos, arrows_size, "craft_arrow");
	arrowUp_tr = arrowUp->getComponent<Transform>();
	arrowDown_tr = arrowDown->getComponent<Transform>();
	arrowDown->getComponent<Image>()->setFlip(SDL_FLIP_VERTICAL);



	Vector2D craftButton_pos = { bg_tr->getPos().getX() + bg_tr->getW() * (3.0f / 4.0f) - 132.5f, bg_tr->getPos().getY() + bg_tr->getH() - 105.0f / 1.5f };

	//BOTON DE CRAFTEO
	setImg(craftButton, craftButton_pos, Vector2D{ 265,105 }, "craft_slot_box");
	craftButton_tr = craftButton->getComponent<Transform>();
}

void Workshop::setWorkshopItems(vector<ITEMS>&& items) {
	workshopItems = move(items);

	//INICIALIZACION SLOTS DE LA LISTA 
	for (int i = 0; i < workshopItems.size() && i < 4; ++i) {
		Slot aux = { 0,getMngr()->addEntity() };
		setImg(aux.slot, Vector2D(), Vector2D{ 365,105 }, "craft_slot_box");
		craftList.push_back(aux);
	}
	float offsetX = bg_tr->getPos().getX() + 45;
	float offsetY = bg_tr->getPos().getY() + 50;
	for (int i = 0; i < workshopItems.size() && i < 4; ++i) {
		craftList[i].slot->getComponent<Transform>()->setPos(Vector2D{ offsetX,offsetY });
		craftList_tr.push_back(craftList[i].slot->getComponent<Transform>());
		offsetY += craftList[i].slot->getComponent<Transform>()->getH() + 35;
	}
}

void Workshop::init() {
	playerInv = getMngr()->getHandler<Player_hdlr>()->getComponent<Inventory>();
}

void Workshop::setRenderFlag(bool set) {
	renderFlag = set;
}

void Workshop::setImg(Entity* entity, Vector2D pos, Vector2D size, std::string name) {
	entity->addComponent<Transform>(pos, size.getX(), size.getY(), 0);
	entity->addComponent<Image>(&sdlutils().images().at(name));
	getMngr()->addRenderLayer<Interface>(entity);
}

void Workshop::update() {
	getMngr()->refresh();
	if (renderFlag) {
		Vector2D mousePos(ih().getMousePos().first, ih().getMousePos().second);
		if (ih().getMouseButtonState(InputHandler::LEFT) && !mouseClick) {
			std::cout << listIndex << std::endl;
			mouseClick = true;

			if (Collisions::collides(mousePos, 1, 1, bButton_tr->getPos(), bButton_tr->getW(), bButton_tr->getH())) {
				renderFlag = false;
				renderRightWindow = false;
			}
			else if (Collisions::collides(mousePos, 1, 1, arrowUp_tr->getPos(), arrowUp_tr->getW(), arrowUp_tr->getH())) {
				if (listIndex > 0)listIndex--;
			}
			else if (Collisions::collides(mousePos, 1, 1, arrowDown_tr->getPos(), arrowDown_tr->getW(), arrowDown_tr->getH())) {
				int aux = workshopItems.size();
				if (listIndex < aux - 4) listIndex++;
			}

			for (int i = 0; i < workshopItems.size() && i < 4; ++i) {
				if (Collisions::collides(mousePos, 1, 1, craftList_tr[i]->getPos(), craftList_tr[i]->getW(), craftList_tr[i]->getH())) {
					renderRightWindow = true;
					rightWindowIndex = craftList[i].index;
				}
			}

			if (renderRightWindow) {
				if (Collisions::collides(mousePos, 1, 1, craftButton_tr->getPos(), craftButton_tr->getW(), craftButton_tr->getH())) {
					std::cout << "se vienen cositas" << std::endl;
				}
			}
		}
		else if (!ih().getMouseButtonState(InputHandler::LEFT)) { mouseClick = false; }
	}
}

void Workshop::render() {
	getMngr()->refresh();
	if (renderFlag) {
		bg->render();
		bButton->render();

		arrowUp->render();
		arrowDown->render();

		for (int i = 0; i < workshopItems.size() && i < 4; ++i) {
			craftList[i].index = listIndex + i;
			craftList[i].slot->render();

			int imgRow = ITEMS_INFO[craftSys->getCrafts()->find(workshopItems[craftList[i].index])->first].row;
			int imgCol = ITEMS_INFO[craftSys->getCrafts()->find(workshopItems[craftList[i].index])->first].col;
			std::string itemName = ITEMS_INFO[craftSys->getCrafts()->find(workshopItems[craftList[i].index])->first].itemName;
			float offsetX = craftList_tr[i]->getPos().getX() + 35;
			float offsetY = craftList_tr[i]->getPos().getY() + 17.5f;

			renderImg(offsetX, offsetY, imgRow, imgCol);

			Texture* text = new Texture(sdlutils().renderer(), itemName, sdlutils().fonts().at("ARIAL24"), build_sdlcolor(0xffffffff));
			SDL_Rect dest{ offsetX + 80 ,craftList_tr[i]->getPos().getY() + craftList_tr[i]->getH() / 2 - text->height() / 2  ,text->width(),text->height() };
			text->render(dest, 0);
			delete text;

			rightWindowRender();
		}
	}
}

void Workshop::rightWindowRender() {
	if (renderRightWindow) {

		float offsetX = bg_tr->getPos().getX() + bg_tr->getW() * (3.0f / 4.0f);
		float offsetY = bg_tr->getPos().getY() + 35;

		std::string itemName = ITEMS_INFO[craftSys->getCrafts()->find(workshopItems[rightWindowIndex])->first].itemName;

		Texture* text = new Texture(sdlutils().renderer(), itemName, sdlutils().fonts().at("ARIAL32"), build_sdlcolor(0xffffffff));
		SDL_Rect dest{ offsetX - text->width() / 2  , offsetY ,text->width(),text->height() };
		text->render(dest, 0);

		offsetY += text->height() + 25;
		delete text;

		int imgRow = ITEMS_INFO[craftSys->getCrafts()->find(workshopItems[rightWindowIndex])->first].row;
		int imgCol = ITEMS_INFO[craftSys->getCrafts()->find(workshopItems[rightWindowIndex])->first].col;
		renderImg(offsetX - 32, offsetY, imgRow, imgCol);

		offsetY += 90;

		text = new Texture(sdlutils().renderer(), "Needed items: ", sdlutils().fonts().at("ARIAL32"), build_sdlcolor(0xffffffff));
		dest = { (int)(offsetX - text->width() / 2)  , (int)offsetY ,text->width(),text->height() };
		text->render(dest, 0);

		offsetY += text->height() + 35;
		delete text;
		offsetX = bg_tr->getPos().getX() + bg_tr->getW() / 2 + 30;

		vector<I> itemsNeeded = craftSys->getCrafts()->find(workshopItems[rightWindowIndex])->second;
		for (int i = 0; i < itemsNeeded.size(); ++i) {
			renderImg(offsetX, offsetY, ITEMS_INFO[itemsNeeded[i].name].row, ITEMS_INFO[itemsNeeded[i].name].col, 48, 48);

			//ESPERAR A QUE YOJHAN CAMBIE LO DEL INVENTARIO
			/*for (Item* item : playerInv->getItems()) {
				if (item->getItemInfo()->name() == ITEMS_INFO[itemsNeeded[i].name)
			}*/


			text = new Texture(sdlutils().renderer(), to_string(itemsNeeded[i].cantidad), sdlutils().fonts().at("ARIAL24"), build_sdlcolor(0xffffffff));
			dest = { (int)(offsetX + 48) , (int)offsetY + 48 - text->height() / 2 ,text->width(),text->height() };
			text->render(dest, 0);
			delete text;

			text = new Texture(sdlutils().renderer(), ITEMS_INFO[itemsNeeded[i].name].itemName, sdlutils().fonts().at("ARIAL32"), build_sdlcolor(0xffffffff));
			dest = { (int)(offsetX + 80) , (int)offsetY + 24 - text->height() / 2 ,text->width(),text->height() };
			text->render(dest, 0);
			delete text;

			offsetY += 48 + 20;

			craftButton->render();
			text = new Texture(sdlutils().renderer(), "CRAFT", sdlutils().fonts().at("ARIAL32"), build_sdlcolor(0xffffffff));
			dest = { (int)(craftButton_tr->getPos().getX() + craftButton_tr->getW() / 2 - text->width() / 2),
				(int)(craftButton_tr->getPos().getY() + craftButton_tr->getH() / 2 - text->height() / 2),text->width(),text->height() };
			text->render(dest, 0);
			delete text;
		}
	}
}

void Workshop::renderImg(float posX, float posY, int row, int col, int sizeX, int sizeY) {
	Entity* aux = getMngr()->addEntity();
	aux->addComponent<Transform>(Vector2D{ posX,posY }, sizeX, sizeY, 0);
	Component* img = aux->addComponent<Image>(&sdlutils().images().at("items"), 4, 3, row, col);
	img->render();

	aux->setActive(false);
}
