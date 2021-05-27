#include "workshop.h"
#include "../classes/shelter_scene.h"

Workshop::Workshop(Manager* realMngr_, Manager* mngr_, CraftingSystem* cs, ShelterScene* shelterScene_) : Entity(mngr_) {
	//EL MANAGER FALSO ES PARA PODER RENDERIZAR ENTIDADES POR SEPARADO SIN QUE SE HAGA DE FORMA AUTOMATICA
	craftSys = cs;
	realMngr_->addEntity(this);
	realMngr_->addRenderLayer<Interface>(this);

	renderFlag = false;
	listIndex = 0;
	mouseClick = false;
	loot = nullptr;

	falseMngr = mngr_;

	playerInv = realMngr_->getHandler<Player_hdlr>()->getComponent<InventoryController>()->inventory;
	playerTr = realMngr_->getHandler<Player_hdlr>()->getComponent<Transform>();

	renderRightWindow = false;
	rightWindowIndex = 0;

	weapon = static_cast<Player*>(realMngr_->getHandler<Player_hdlr>())->getWeapon();

	weaponTr = falseMngr->addEntity()->addComponent<Transform>(Vector2D(), 128, 128);
	weaponImg = weaponTr->getEntity()->addComponent<Image>(&sdlutils().images().at("weapons"), 3, 3, 0, 0, true);
	falseMngr->addRenderLayer<Interface>(weaponTr->getEntity());

	//INICIALIZACION IMAGENES DEL FONDO, FLECHAS Y X PARA SALIR
	bg = mngr_->addEntity();
	bButton = mngr_->addEntity();
	arrowUp = mngr_->addEntity();
	arrowDown = mngr_->addEntity();
	arrowLeft = mngr_->addEntity();
	arrowRight = mngr_->addEntity();
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

	float offsetX = bg_tr->getPos().getX() + bg_tr->getW() * (3.0f / 4.0f);
	float offsetY = bg_tr->getPos().getY() + 35;
	arrowLeft_tr = arrowLeft->addComponent<Transform>(Vector2D(offsetX - 128 - 16, offsetY + 64), 64, 64, -90);
	arrowRight_tr = arrowRight->addComponent<Transform>(Vector2D(offsetX + 128 - 48, offsetY + 64), 64, 64, 90);

	arrowLeft->addComponent<Image>(&sdlutils().images().at("craft_arrow"), 1, 1, 0, 0, true);
	arrowRight->addComponent<Image>(&sdlutils().images().at("craft_arrow"), 1, 1, 0, 0, true);
	mngr_->addRenderLayer<Interface>(arrowLeft);
	mngr_->addRenderLayer<Interface>(arrowRight);

	Vector2D craftButton_pos = { bg_tr->getPos().getX() + bg_tr->getW() * (3.0f / 4.0f) - 132.5f, bg_tr->getPos().getY() + bg_tr->getH() - 105.0f / 1.5f };

	//BOTON DE CRAFTEO
	setImg(craftButton, craftButton_pos, Vector2D{ 265,105 }, "craft_slot_box");
	craftButton_tr = craftButton->getComponent<Transform>();

	//referencia para usar acciones
	shelterScene = shelterScene_;
}

void Workshop::closeCraft()
{
	loot->Interact();
	loot->getEntity()->setActive(false);
	loot = nullptr;
	renderFlag = true;
	renderRightWindow = true;
	setLeftRender();
	setRightRender();

}

void Workshop::setWorkshopItems(vector<ITEMS>&& items) {
	workshopItems = move(items);

	//INICIALIZACION SLOTS DE LA LISTA 
	for (int i = 0; i < workshopItems.size() && i < 4; ++i) {
		Slot aux = { 0,falseMngr->addEntity() };
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

void Workshop::setRenderFlag(bool set) {
	renderFlag = set;
	if (set)
		playerTr->getEntity()->setActive(false);

	setLeftRender();
	ih().clearState();
}

void Workshop::setImg(Entity* entity, Vector2D pos, Vector2D size, std::string name) {
	entity->addComponent<Transform>(pos, size.getX(), size.getY(), 0);
	entity->addComponent<Image>(&sdlutils().images().at(name), 1, 1, 0, 0, true);
	falseMngr->addRenderLayer<Interface>(entity);
}

void Workshop::setLeftRender() {
	for (int i = 0; i < leftRenderTexts.size(); ++i) {
		delete  leftRenderTexts[i];
	}
	leftRenderTexts.clear();

	for (int i = 0; i < leftRenderImgs.size(); ++i) {
		leftRenderImgs[i]->setDead(true);
		leftRenderImgs[i]->setActive(false);
	}
	falseMngr->refresh();
	leftRenderImgs.clear();

	for (int i = 0; i < workshopItems.size() && i < 4; ++i) {
		craftList[i].index = listIndex + i;
		auto item = craftSys->getItemInfo(workshopItems[craftList[i].index]);
		std::string itemName = item->strName();
		leftRenderTexts.push_back(new Texture(sdlutils().renderer(), itemName, sdlutils().fonts().at("OrbitronRegular"), build_sdlcolor(0xffffffff)));


		int imgRow = item->row();
		int imgCol = item->col();

		float offsetX = craftList_tr[i]->getPos().getX() + 35;
		float offsetY = craftList_tr[i]->getPos().getY() + 17.5f;

		delete item;

		Entity* aux = falseMngr->addEntity();
		aux->addComponent<Transform>(Vector2D{ offsetX,offsetY }, 64, 64, 0);
		Component* img = aux->addComponent<Image>(&sdlutils().images().at("items"), 8, 3, imgRow, imgCol, true);

		leftRenderImgs.push_back(aux);
	}
}

void Workshop::setRightRender() {
	for (int i = 0; i < rightRenderTexts.size(); ++i) {
		delete  rightRenderTexts[i];
	}
	rightRenderTexts.clear();

	for (int i = 0; i < rightRenderImgs.size(); ++i) {
		rightRenderImgs[i]->setDead(true);
		rightRenderImgs[i]->setActive(false);
	}
	falseMngr->refresh();
	rightRenderImgs.clear();

	if (workshopItems[rightWindowIndex] != WEAPON_UPGRADE || static_cast<Player*>(playerTr->getEntity())->getWeapon()->tierOfWeapon() < 2) {
		auto rightWindowItem = craftSys->getItemInfo(workshopItems[rightWindowIndex]);
		std::string itemName = rightWindowItem->strName();
		rightRenderTexts.push_back(new Texture(sdlutils().renderer(), itemName, sdlutils().fonts().at("Orbitron32"), build_sdlcolor(0xffffffff)));
		rightRenderTexts.push_back(new Texture(sdlutils().renderer(), "Needed items: ", sdlutils().fonts().at("Orbitron32"), build_sdlcolor(0xffffffff)));

		float offsetX = bg_tr->getPos().getX() + bg_tr->getW() * (3.0f / 4.0f);
		float offsetY = rightRenderTexts[0]->height() + 25;
		int imgRow = rightWindowItem->row();
		int imgCol = rightWindowItem->col();

		delete rightWindowItem;

		Entity* aux = falseMngr->addEntity();
		aux->addComponent<Transform>(Vector2D{ offsetX - 32,offsetY + 80 }, 64, 64, 0);
		Component* img = aux->addComponent<Image>(&sdlutils().images().at("items"), 8, 3, imgRow, imgCol, true);
		img->render();

		rightRenderImgs.push_back(aux);

		offsetY = 312;
		offsetX = bg_tr->getPos().getX() + bg_tr->getW() / 2 + 30;

		vector<ItemInfo*> itemsNeeded = craftSys->getCrafts()->find(workshopItems[rightWindowIndex])->second;
		for (int i = 0; i < itemsNeeded.size(); ++i) {
			int aux = 0;
			list<Item*> items = playerInv->getItems();
			for (auto it = items.begin(); it != items.end(); ++it)
			{
				if ((*it)->getItemInfo()->name() == itemsNeeded[i]->name())
					aux++;
			}

			rightRenderTexts.push_back(new Texture(sdlutils().renderer(), to_string(aux) + "/" + to_string(itemsNeeded[i]->getAmount()), sdlutils().fonts().at("OrbitronRegular"), build_sdlcolor(0xffffffff)));

			rightRenderTexts.push_back(new Texture(sdlutils().renderer(), itemsNeeded[i]->strName(), sdlutils().fonts().at("OrbitronRegular"), build_sdlcolor(0xffffffff)));

			Entity* aux2 = falseMngr->addEntity();
			aux2->addComponent<Transform>(Vector2D{ offsetX,offsetY }, 48, 48, 0);
			Component* img = aux2->addComponent<Image>(&sdlutils().images().at("items"), 8, 3, itemsNeeded[i]->row(), itemsNeeded[i]->col(), true);
			img->render();
			rightRenderImgs.push_back(aux2);

			offsetY += 48 + 20;
		}

		rightRenderTexts.push_back(new Texture(sdlutils().renderer(), "CRAFT", sdlutils().fonts().at("OrbitronRegular"), build_sdlcolor(0xffffffff)));
	}
	else {
		//weapon is at its maximun tier and cant be upgraded
		rightRenderTexts.push_back(new Texture(sdlutils().renderer(), "The equiped weapon is ", sdlutils().fonts().at("Orbitron32"), build_sdlcolor(0xffffffff)));

		rightRenderTexts.push_back(new Texture(sdlutils().renderer(), "at its maximun tier", sdlutils().fonts().at("Orbitron32"), build_sdlcolor(0xffffffff)));

		rightRenderTexts.push_back(new Texture(sdlutils().renderer(), "and cant be upgraded", sdlutils().fonts().at("Orbitron32"), build_sdlcolor(0xffffffff)));

	}
}

void Workshop::update() {
	falseMngr->refresh();

	if (loot != nullptr && ih().isKeyDown(SDL_SCANCODE_E)) {
		if (!loot->getInventory()->getItems().empty()) {
			craftSys->restoreCraft();
			shelterScene->addAction();
		}
		closeCraft();
		ih().clearState();
	}

	if (renderFlag) {
		Vector2D mousePos(ih().getMousePos().first, ih().getMousePos().second);

		if (ih().isKeyDown(SDL_SCANCODE_E)) {
			renderFlag = false;
			renderRightWindow = false;
			playerTr->getEntity()->setActive(true);
			ih().clearState();
		}

		if (ih().getMouseButtonState(InputHandler::LEFT) && !mouseClick) {
			mouseClick = true;

			if (Collisions::collides(mousePos, 1, 1, bButton_tr->getPos(), bButton_tr->getW(), bButton_tr->getH())) {
				renderFlag = false;
				playerTr->getEntity()->setActive(true);
				renderRightWindow = false;
			}
			else if (Collisions::collides(mousePos, 1, 1, arrowUp_tr->getPos(), arrowUp_tr->getW(), arrowUp_tr->getH())) {
				if (listIndex > 0)listIndex--;

				setLeftRender();
			}
			else if (Collisions::collides(mousePos, 1, 1, arrowDown_tr->getPos(), arrowDown_tr->getW(), arrowDown_tr->getH())) {
				int aux = workshopItems.size();
				if (listIndex < aux - 4) listIndex++;

				setLeftRender();
			}

			for (int i = 0; i < workshopItems.size() && i < 4; ++i) {
				if (Collisions::collides(mousePos, 1, 1, craftList_tr[i]->getPos(), craftList_tr[i]->getW(), craftList_tr[i]->getH())) {
					renderRightWindow = true;
					rightWindowIndex = craftList[i].index;

					setRightRender();
				}
			}

			if (renderRightWindow) {
				if (Collisions::collides(mousePos, 1, 1, craftButton_tr->getPos(), craftButton_tr->getW(), craftButton_tr->getH())) {
					//si tengo acciones
					if (shelterScene->getActions() > 0) {
						if (workshopItems[rightWindowIndex] == WEAPON_UPGRADE) {
							bool isCraftable = craftSys->CraftItem(workshopItems[rightWindowIndex], craftButton_tr->getPos().getX() * 3 / 2, consts::WINDOW_HEIGHT / 3, this, false);
							WeaponBehaviour* weapon = static_cast<Player*>(playerTr->getEntity())->getWeapon();
							if (isCraftable && weapon->tierOfWeapon() < 3) {
								renderRightWindow = false;
								weapon->upgradeCurrentWeapon();
								//gastar accion
								shelterScene->useAction();
							}

						}
						else {
							bool isCraftable = craftSys->CraftItem(workshopItems[rightWindowIndex], craftButton_tr->getPos().getX() * 3 / 2, consts::WINDOW_HEIGHT / 3, this);
							if (isCraftable) {
								renderRightWindow = false;
								renderFlag = false;
								shelterScene->useAction();
							}
						}
					}
				}
				if (Collisions::collides(mousePos, 1, 1, arrowLeft_tr->getPos(), arrowLeft_tr->getW(), arrowLeft_tr->getH())) {
					//Lo pongo 2 veces aposta (no quitar)
					weapon->changeWeapon();
					weapon->changeWeapon();
					setRightRender();
				}
				else if (Collisions::collides(mousePos, 1, 1, arrowRight_tr->getPos(), arrowRight_tr->getW(), arrowRight_tr->getH())) {
					weapon->changeWeapon();
					setRightRender();
				}
			}
		}
		else if (!ih().getMouseButtonState(InputHandler::LEFT)) { mouseClick = false; }
	}

	if (loot != nullptr) {
		Vector2D mousePos(ih().getMousePos().first, ih().getMousePos().second);

		mouseClick = true;

		if (loot->getInventory()->getItems().empty()) {
			closeCraft();
			renderFlag = true;
		}
		else if (ih().getMouseButtonState(InputHandler::LEFT) && !mouseClick)
			if (Collisions::collides(mousePos, 1, 1, bButton_tr->getPos(), bButton_tr->getW(), bButton_tr->getH())) {
				craftSys->restoreCraft();
				shelterScene->addAction();
			}
	}
}

void Workshop::render() {
	falseMngr->refresh();
	if (renderFlag && loot == nullptr) {
		bg->render();
		bButton->render();

		arrowUp->render();
		arrowDown->render();

		for (int i = 0; i < workshopItems.size() && i < 4; ++i) {
			craftList[i].slot->render();

			leftRenderImgs[i]->render();

			float offsetX = craftList_tr[i]->getPos().getX() + 35;

			SDL_Rect dest{ offsetX + 80 ,craftList_tr[i]->getPos().getY() + craftList_tr[i]->getH() / 2 - leftRenderTexts[i]->height() / 2  ,leftRenderTexts[i]->width(),leftRenderTexts[i]->height() };
			leftRenderTexts[i]->render(dest, 0);

			rightWindowRender();
		}
	}
	else if (loot != nullptr) {
		bButton->render();
	}
}

void Workshop::rightWindowRender() {
	if (renderRightWindow) {
		float offsetX = bg_tr->getPos().getX() + bg_tr->getW() * (3.0f / 4.0f);
		float offsetY = bg_tr->getPos().getY() + 35;
		if (workshopItems[rightWindowIndex] != WEAPON_UPGRADE || static_cast<Player*>(playerTr->getEntity())->getWeapon()->tierOfWeapon() < 2) {

			std::string itemName = craftSys->getItemInfo(workshopItems[rightWindowIndex])->strName();

			SDL_Rect dest{ offsetX - rightRenderTexts[0]->width() / 2  , offsetY ,rightRenderTexts[0]->width(),rightRenderTexts[0]->height() };
			rightRenderTexts[0]->render(dest, 0);

			offsetY += rightRenderTexts[0]->height() + 25;

			int imgRow = craftSys->getItemInfo(workshopItems[rightWindowIndex])->row();
			int imgCol = craftSys->getItemInfo(workshopItems[rightWindowIndex])->col();

			if (workshopItems[rightWindowIndex] == WEAPON_UPGRADE) {
				weaponTr->setPos(Vector2D(offsetX - 64, offsetY - 16));
				renderWeaponUpgrade();
				arrowLeft->render();
				arrowRight->render();
			}
			else rightRenderImgs[0]->render();

			offsetY += 90;

			dest = { (int)(offsetX - rightRenderTexts[1]->width() / 2)  , (int)offsetY ,rightRenderTexts[1]->width(),rightRenderTexts[1]->height() };
			rightRenderTexts[1]->render(dest, 0);

			offsetY += rightRenderTexts[1]->height() + 35;
			offsetX = bg_tr->getPos().getX() + bg_tr->getW() / 2 + 30;


			vector<ItemInfo*> itemsNeeded = craftSys->getCrafts()->find(workshopItems[rightWindowIndex])->second;
			for (int i = 0; i < itemsNeeded.size(); ++i) {
				rightRenderImgs[1 + i]->render();

				dest = { (int)(offsetX + 30) , (int)offsetY + 48 - rightRenderTexts[2 * (i + 1)]->height() / 2 ,	rightRenderTexts[2 * (i + 1)]->width(),	rightRenderTexts[2 * (i + 1)]->height() };
				rightRenderTexts[2 * (i + 1)]->render(dest, 0);

				dest = { (int)(offsetX + 80) , (int)offsetY + 24 - rightRenderTexts[2 * (i + 1) + 1]->height() / 2 ,	rightRenderTexts[2 * (i + 1) + 1]->width(),	rightRenderTexts[2 * (i + 1) + 1]->height() };
				rightRenderTexts[2 * (i + 1) + 1]->render(dest, 0);

				offsetY += 48 + 20;
			}

			dest = { (int)(craftButton_tr->getPos().getX() + craftButton_tr->getW() / 2 - rightRenderTexts[rightRenderTexts.size() - 1]->width() / 2),
				(int)(craftButton_tr->getPos().getY() + craftButton_tr->getH() / 2 - rightRenderTexts[rightRenderTexts.size() - 1]->height() / 2),
				rightRenderTexts[rightRenderTexts.size() - 1]->width(),	rightRenderTexts[rightRenderTexts.size() - 1]->height() };

			craftButton->render();
			rightRenderTexts[rightRenderTexts.size() - 1]->render(dest, 0);
		}
		else {

			offsetY += 61;

			if (workshopItems[rightWindowIndex] == WEAPON_UPGRADE) {
				weaponTr->setPos(Vector2D(offsetX - 64, offsetY - 16));
				renderWeaponUpgrade();
				arrowLeft->render();
				arrowRight->render();
			}

			offsetY += 150;


			//weapon is at its maximun tier and cant be upgraded
			SDL_Rect dest{ offsetX - rightRenderTexts[0]->width() / 2  , offsetY ,rightRenderTexts[0]->width(),rightRenderTexts[0]->height() };
			rightRenderTexts[0]->render(dest, 0);
			offsetY += rightRenderTexts[0]->height() + 25;

			dest = { (int)offsetX - rightRenderTexts[1]->width() / 2  ,(int)offsetY ,rightRenderTexts[1]->width(),rightRenderTexts[1]->height() };
			rightRenderTexts[1]->render(dest, 0);
			offsetY += rightRenderTexts[1]->height() + 25;

			dest = { (int)offsetX - rightRenderTexts[2]->width() / 2  ,(int)offsetY ,rightRenderTexts[2]->width(),rightRenderTexts[2]->height() };
			rightRenderTexts[2]->render(dest, 0);
		}
	}
}


void Workshop::renderWeaponUpgrade() {
	weaponImg->changeFrame(weapon->tierOfWeapon(), (int)weapon->typeOfWeapon());

	weaponImg->render();
}

void Workshop::renderImg(float posX, float posY, int row, int col, int sizeX, int sizeY) {
	Entity* aux = falseMngr->addEntity();
	aux->addComponent<Transform>(Vector2D{ posX,posY }, sizeX, sizeY, 0);
	Component* img = aux->addComponent<Image>(&sdlutils().images().at("items"), 8, 3, row, col, true);
	img->render();

	aux->setDead(true);
	aux->setActive(false);
}
