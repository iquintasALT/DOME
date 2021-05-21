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

	weapon = static_cast<Player*>(realMngr_->getHandler<Player_hdlr>())->getCurrentWeapon();

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
	getMngr()->addRenderLayer<Interface>(arrowLeft);
	getMngr()->addRenderLayer<Interface>(arrowRight);

	Vector2D craftButton_pos = { bg_tr->getPos().getX() + bg_tr->getW() * (3.0f / 4.0f) - 132.5f, bg_tr->getPos().getY() + bg_tr->getH() - 105.0f / 1.5f };

	//BOTON DE CRAFTEO
	setImg(craftButton, craftButton_pos, Vector2D{ 265,105 }, "craft_slot_box");
	craftButton_tr = craftButton->getComponent<Transform>();

	//referencia para usar acciones
	shelterScene = shelterScene_;
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

void Workshop::setRenderFlag(bool set) {
	renderFlag = set;
	if (set)
		playerTr->getEntity()->setActive(false);
}

void Workshop::setImg(Entity* entity, Vector2D pos, Vector2D size, std::string name) {
	entity->addComponent<Transform>(pos, size.getX(), size.getY(), 0);
	entity->addComponent<Image>(&sdlutils().images().at(name), 1, 1, 0, 0, true);
	getMngr()->addRenderLayer<Interface>(entity);
}

void Workshop::update() {
	falseMngr->refresh();

	if (renderFlag) {
		Vector2D mousePos(ih().getMousePos().first, ih().getMousePos().second);


		if (ih().getMouseButtonState(InputHandler::LEFT) && !mouseClick) {
			mouseClick = true;

			if (Collisions::collides(mousePos, 1, 1, bButton_tr->getPos(), bButton_tr->getW(), bButton_tr->getH())) {
				renderFlag = false;
				playerTr->getEntity()->setActive(true);
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
					//si tengo acciones
					if (shelterScene->getActions() > 0) {
						if (workshopItems[rightWindowIndex] == WEAPON_UPGRADE) {
							bool isCraftable = craftSys->CraftItem(workshopItems[rightWindowIndex], craftButton_tr->getPos().getX() * 3 / 2, consts::WINDOW_HEIGHT / 3, this, false);
							WeaponBehaviour* weapon = static_cast<Player*>(playerTr->getEntity())->getCurrentWeapon();
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
							}
						}
					}
				}
				if (Collisions::collides(mousePos, 1, 1, arrowLeft_tr->getPos(), arrowLeft_tr->getW(), arrowLeft_tr->getH())) {
					//Lo pongo 2 veces aposta (no quitar)
					weapon->changeWeapon();
					weapon->changeWeapon();
				}
				else if (Collisions::collides(mousePos, 1, 1, arrowRight_tr->getPos(), arrowRight_tr->getW(), arrowRight_tr->getH())) {
					weapon->changeWeapon();
				}
			}
		}
		else if (!ih().getMouseButtonState(InputHandler::LEFT)) { mouseClick = false; }
	}

	if (loot != nullptr) {
		Vector2D mousePos(ih().getMousePos().first, ih().getMousePos().second);
		if (ih().getMouseButtonState(InputHandler::LEFT) && !mouseClick) {
			mouseClick = true;

			if (Collisions::collides(mousePos, 1, 1, bButton_tr->getPos(), bButton_tr->getW(), bButton_tr->getH())) {

				if (loot->getInventory()->getItems().empty()) {
					craftSys->FinishCraft();
					//gastar accion
					shelterScene->useAction();
				}

				loot->Interact();
				loot->getEntity()->setActive(false);
				loot = nullptr;
				renderFlag = true;
				renderRightWindow = true;
			}
		}
		else if (!ih().getMouseButtonState(InputHandler::LEFT)) { mouseClick = false; }
	}
}

void Workshop::render() {
	falseMngr->refresh();
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

			Texture* text = new Texture(sdlutils().renderer(), itemName, sdlutils().fonts().at("OrbitronRegular"), build_sdlcolor(0xffffffff));
			SDL_Rect dest{ offsetX + 80 ,craftList_tr[i]->getPos().getY() + craftList_tr[i]->getH() / 2 - text->height() / 2  ,text->width(),text->height() };
			text->render(dest, 0);
			delete text;

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
		if (workshopItems[rightWindowIndex] != WEAPON_UPGRADE || static_cast<Player*>(playerTr->getEntity())->getCurrentWeapon()->tierOfWeapon() < 2) {

			std::string itemName = ITEMS_INFO[craftSys->getCrafts()->find(workshopItems[rightWindowIndex])->first].itemName;

			Texture* text = new Texture(sdlutils().renderer(), itemName, sdlutils().fonts().at("Orbitron32"), build_sdlcolor(0xffffffff));
			SDL_Rect dest{ offsetX - text->width() / 2  , offsetY ,text->width(),text->height() };
			text->render(dest, 0);

			offsetY += text->height() + 25;
			delete text;

			int imgRow = ITEMS_INFO[craftSys->getCrafts()->find(workshopItems[rightWindowIndex])->first].row;
			int imgCol = ITEMS_INFO[craftSys->getCrafts()->find(workshopItems[rightWindowIndex])->first].col;


			if (workshopItems[rightWindowIndex] == WEAPON_UPGRADE) {
				weaponTr->setPos(Vector2D(offsetX - 64, offsetY - 16));
				renderWeaponUpgrade();
				arrowLeft->render();
				arrowRight->render();
			}
			else renderImg(offsetX - 32, offsetY, imgRow, imgCol);

			offsetY += 90;

			text = new Texture(sdlutils().renderer(), "Needed items: ", sdlutils().fonts().at("Orbitron32"), build_sdlcolor(0xffffffff));
			dest = { (int)(offsetX - text->width() / 2)  , (int)offsetY ,text->width(),text->height() };
			text->render(dest, 0);

			offsetY += text->height() + 35;
			delete text;
			offsetX = bg_tr->getPos().getX() + bg_tr->getW() / 2 + 30;

			vector<I> itemsNeeded = craftSys->getCrafts()->find(workshopItems[rightWindowIndex])->second;
			for (int i = 0; i < itemsNeeded.size(); ++i) {
				renderImg(offsetX, offsetY, ITEMS_INFO[itemsNeeded[i].name].row, ITEMS_INFO[itemsNeeded[i].name].col, 48, 48);

				int aux = 0;
				list<Item*> items = playerInv->getItems();
				for (auto it = items.begin(); it != items.end(); ++it)
				{
					if ((*it)->getItemInfo()->name() == itemsNeeded[i].name)
						aux++;
				}


				text = new Texture(sdlutils().renderer(), to_string(aux) + "/" + to_string(itemsNeeded[i].cantidad), sdlutils().fonts().at("OrbitronRegular"), build_sdlcolor(0xffffffff));
				dest = { (int)(offsetX + 30) , (int)offsetY + 48 - text->height() / 2 ,text->width(),text->height() };
				text->render(dest, 0);
				delete text;

				text = new Texture(sdlutils().renderer(), ITEMS_INFO[itemsNeeded[i].name].itemName, sdlutils().fonts().at("OrbitronRegular"), build_sdlcolor(0xffffffff));
				dest = { (int)(offsetX + 80) , (int)offsetY + 24 - text->height() / 2 ,text->width(),text->height() };
				text->render(dest, 0);
				delete text;

				offsetY += 48 + 20;

				craftButton->render();
				text = new Texture(sdlutils().renderer(), "CRAFT", sdlutils().fonts().at("OrbitronRegular"), build_sdlcolor(0xffffffff));
				dest = { (int)(craftButton_tr->getPos().getX() + craftButton_tr->getW() / 2 - text->width() / 2),
					(int)(craftButton_tr->getPos().getY() + craftButton_tr->getH() / 2 - text->height() / 2),text->width(),text->height() };
				text->render(dest, 0);
				delete text;
			}

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
			Texture* text = new Texture(sdlutils().renderer(), "The equiped weapon is ", sdlutils().fonts().at("Orbitron32"), build_sdlcolor(0xffffffff));
			SDL_Rect dest{ offsetX - text->width() / 2  , offsetY ,text->width(),text->height() };
			text->render(dest, 0);
			offsetY += text->height() + 25;  delete text;

			text = new Texture(sdlutils().renderer(), "at its maximun tier", sdlutils().fonts().at("Orbitron32"), build_sdlcolor(0xffffffff));
			dest = { (int)offsetX - text->width() / 2  ,(int)offsetY ,text->width(),text->height() };
			text->render(dest, 0);
			offsetY += text->height() + 25;  delete text;

			text = new Texture(sdlutils().renderer(), "and cant be upgraded", sdlutils().fonts().at("Orbitron32"), build_sdlcolor(0xffffffff));
			dest = { (int)offsetX - text->width() / 2  ,(int)offsetY ,text->width(),text->height() };
			text->render(dest, 0);
		}
	}
}


void Workshop::renderWeaponUpgrade() {
	if (weapon->typeOfWeapon() == Weapon::WeaponType::CLASSIC) {
		if (weapon->tierOfWeapon() == 0) {
			weaponImg->changeFrame(0, 0);
		}
		else if (weapon->tierOfWeapon() == 1) {
			weaponImg->changeFrame(1, 0);
		}
		else {
			weaponImg->changeFrame(2, 0);
		}
	}
	else if (weapon->typeOfWeapon() == Weapon::WeaponType::RICOCHET) {
		if (weapon->tierOfWeapon() == 0) {
			weaponImg->changeFrame(0, 1);
		}
		else if (weapon->tierOfWeapon() == 1) {
			weaponImg->changeFrame(1, 1);
		}
		else {
			weaponImg->changeFrame(2, 1);
		}
	}
	else if (weapon->typeOfWeapon() == Weapon::WeaponType::LASER) {
		if (weapon->tierOfWeapon() == 0) {
			weaponImg->changeFrame(0, 2);
		}
		else if (weapon->tierOfWeapon() == 1) {
			weaponImg->changeFrame(1, 2);
		}
		else {
			weaponImg->changeFrame(2, 2);
		}
	}
	weaponImg->render();
}

void Workshop::renderImg(float posX, float posY, int row, int col, int sizeX, int sizeY) {
	Entity* aux = getMngr()->addEntity();
	aux->addComponent<Transform>(Vector2D{ posX,posY }, sizeX, sizeY, 0);
	Component* img = aux->addComponent<Image>(&sdlutils().images().at("items"), 8, 3, row, col, true);
	img->render();

	aux->setActive(false);
}
