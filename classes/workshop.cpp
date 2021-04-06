#include "workshop.h"

Workshop::Workshop(Manager* mngr_, CraftingSystem* cs) : GameEntity(mngr_) {
	craftSys = cs;
	mngr_->addEntity(this);
	renderFlag = false;
	listIndex = 0;
	mouseClick = false;
	workshopItems = { SPACESHIP_ROCKETS, METAL_PLATES, WEAPON_UPGRADE,  CLASSIC_AMMO, BACKPACK_UPGRADE, ARMOUR_UPGRADE };


	//INICIALIZACION IMAGENES DEL FONDO, FLECHAS Y X PARA SALIR
	bg = mngr_->addEntity();
	bButton = mngr_->addEntity();
	arrowUp = mngr_->addEntity();
	arrowDown = mngr_->addEntity();

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

	//INICIALIZACION SLOTS DE LA LISTA 
	for (int i = 0; i < 4; ++i) {
		Slot aux = { 0,mngr_->addEntity() };
		setImg(aux.slot, Vector2D(), Vector2D{ 365,105 }, "craft_slot_box");
		craftList.push_back(aux);
	}
	float offsetX = bg_tr->getPos().getX() + 45;
	float offsetY = bg_tr->getPos().getY() + 50;
	for (int i = 0; i < 4; ++i) {
		craftList[i].slot->getComponent<Transform>()->setPos(Vector2D{ offsetX,offsetY });
		craftList_tr.push_back(craftList[i].slot->getComponent<Transform>());
		offsetY += craftList[i].slot->getComponent<Transform>()->getH() + 35;
	}
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
		if (ih().getMouseButtonState(InputHandler::LEFT) && !mouseClick) {
			mouseClick = true;

			if (Collisions::collides(mousePos, 1, 1, bButton_tr->getPos(), bButton_tr->getW(), bButton_tr->getH()))
				renderFlag = false;
			else if (Collisions::collides(mousePos, 1, 1, arrowUp_tr->getPos(), arrowUp_tr->getW(), arrowUp_tr->getH())) {
				if (listIndex > 0)listIndex--;
			}
			else if (Collisions::collides(mousePos, 1, 1, arrowDown_tr->getPos(), arrowDown_tr->getW(), arrowDown_tr->getH())) {
				if (listIndex < workshopItems.size() - 4) listIndex++;
			}
		}
		else { mouseClick = false; }
	}
}

void Workshop::render() {
	if (renderFlag) {
		bg->render();
		bButton->render();

		arrowUp->render();
		arrowDown->render();

		for (int i = 0; i < 4; ++i) {
			craftList[i].index = listIndex + i;
			craftList[i].slot->render();

			int imgRow = ITEMS_INFO[craftSys->getCrafts()->find(workshopItems[craftList[i].index])->first].row;
			int imgCol = ITEMS_INFO[craftSys->getCrafts()->find(workshopItems[craftList[i].index])->first].col;
			std::string itemName = ITEMS_INFO[craftSys->getCrafts()->find(workshopItems[craftList[i].index])->first].itemName;
			float offsetX = craftList_tr[i]->getPos().getX() + 35;
			float offsetY = craftList_tr[i]->getPos().getY() + 17.5f;

			Entity* aux = getMngr()->addEntity();
			aux->addComponent<Transform>(Vector2D{ offsetX,offsetY }, Vector2D(), 64, 64, 0);
			aux->addComponent<Image>(&sdlutils().images().at("items"), 3, 3, imgRow, imgCol)->render();
			Texture* text = new Texture(sdlutils().renderer(), itemName, sdlutils().fonts().at("ARIAL24"), build_sdlcolor(0xffffffff));
			SDL_Rect dest{ offsetX + 80 ,craftList_tr[i]->getPos().getY() + craftList_tr[i]->getH() / 2 - text->height() / 2  ,text->width(),text->height() };
			text->render(dest, 0);
			delete text;
			aux->setActive(false);
		}
	}
}