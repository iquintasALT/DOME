#include "spaceship_station.h"
#include "../game/Game.h"
#include "../classes/shelter_scene.h"
#include "../classes/lose_scene.h"

SpaceshipStation::SpaceshipStation(Manager* realMngr_, Manager* mngr_, CraftingSystem* cs, ShelterScene* shelterScene_) : Workshop(mngr_) {
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


	//INICIALIZACION IMAGENES DEL FONDO, FLECHAS Y X PARA SALIR
	bg = mngr_->addEntity();
	bButton = mngr_->addEntity();

	craftButton = mngr_->addEntity();

	Vector2D bg_size = { 930, 630 };
	Vector2D bg_pos = Vector2D(sdlutils().width() / 2 - bg_size.getX() / 2, sdlutils().height() / 2 - bg_size.getY() / 2);
	Vector2D bButton_size = { 65,64 };
	Vector2D bButton_pos = Vector2D(bg_pos.getX() - bButton_size.getX() / 2, bg_pos.getY() - bButton_size.getY() / 2);

	setImg(bg, bg_pos, bg_size, "craft_bg");
	setImg(bButton, bButton_pos, bButton_size, "craft_back_button");
	bg_tr = bg->getComponent<Transform>();
	bButton_tr = bButton->getComponent<Transform>();

	Vector2D craftButton_pos = { bg_tr->getPos().getX() + bg_tr->getW() * (3.0f / 4.0f) - 132.5f, bg_tr->getPos().getY() + bg_tr->getH() - 105.0f / 1.5f };

	//BOTON DE CRAFTEO
	setImg(craftButton, craftButton_pos, Vector2D{ 265,105 }, "craft_slot_box");
	craftButton_tr = craftButton->getComponent<Transform>();

	setWorkshopItems({ SPACESHIP_CABIN,SPACESHIP_RADAR,SPACESHIP_ROCKETS });

	rocketTop = mngr_->addEntity();
	rocketTop->addComponent<Transform>(Vector2D{ bg_pos.getX() + bg_size.getX() * 0.075f,35 }, 320, 213);
	rocketTopImg = rocketTop->addComponent<Image>(&sdlutils().images().at("rocket"), 3, 1, 0, 0, true);
	if (!realMngr_->getGame()->radar)rocketTopImg->setAlpha(125);
	rocketMid = mngr_->addEntity();
	rocketMid->addComponent<Transform>(Vector2D{ bg_pos.getX() + bg_size.getX() * 0.075f,248 }, 320, 213);
	rocketMidImg = rocketMid->addComponent<Image>(&sdlutils().images().at("rocket"), 3, 1, 1, 0, true);
	if (!realMngr_->getGame()->cabin) rocketMidImg->setAlpha(125);
	rocketBot = mngr_->addEntity();
	rocketBot->addComponent<Transform>(Vector2D{ bg_pos.getX() + bg_size.getX() * 0.075f,461 }, 320, 213);
	rocketBotImg = rocketBot->addComponent<Image>(&sdlutils().images().at("rocket"), 3, 1, 2, 0, true);
	if (!realMngr_->getGame()->rockets)rocketBotImg->setAlpha(125);

	falseMngr->addRenderLayer<Interface>(rocketTop);
	falseMngr->addRenderLayer<Interface>(rocketMid);
	falseMngr->addRenderLayer<Interface>(rocketBot);

	//referencia a ShelterScene para usar acciones
	shelterScene = shelterScene_;
}

void SpaceshipStation::setWorkshopItems(vector<ITEMS>&& items) {
	workshopItems = move(items);

	//INICIALIZACION SLOTS DE LA LISTA 
	for (int i = 0; i < workshopItems.size() && i < 4; ++i) {
		int imgRow = ITEMS_INFO[craftSys->getCrafts()->find(workshopItems[i])->first].row;
		int imgCol = ITEMS_INFO[craftSys->getCrafts()->find(workshopItems[i])->first].col;
		std::string itemName = ITEMS_INFO[craftSys->getCrafts()->find(workshopItems[i])->first].itemName;
		Slot aux = { 0,getMngr()->addEntity() };
		aux.slot->addComponent<Transform>(Vector2D(), 64, 64, 0);
		aux.slot->addComponent<Image>(&sdlutils().images().at("items"), 8, 3, imgRow, imgCol, true);
		craftList.push_back(aux);
		falseMngr->addRenderLayer<Interface>(aux.slot);
	}

	float offsetX = bg_tr->getPos().getX() + bg_tr->getW() * 0.25f - 32;
	float offsetY = bg_tr->getPos().getY() + bg_tr->getH() * 0.2f - 32;
	for (int i = 0; i < workshopItems.size() && i < 4; ++i) {
		craftList[i].slot->getComponent<Transform>()->setPos(Vector2D{ offsetX,offsetY });
		craftList_tr.push_back(craftList[i].slot->getComponent<Transform>());
		offsetY += 180;
	}
}

void SpaceshipStation::update() {
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

			for (int i = 0; i < workshopItems.size() && i < 4; ++i) {
				if ((workshopItems[i] == SPACESHIP_CABIN && !mngr_->getGame()->cabin) ||
					(workshopItems[i] == SPACESHIP_ROCKETS && !mngr_->getGame()->rockets)
					|| (workshopItems[i] == SPACESHIP_RADAR && !mngr_->getGame()->radar))
					if (Collisions::collides(mousePos, 1, 1, craftList_tr[i]->getPos(), craftList_tr[i]->getW(), craftList_tr[i]->getH())) {
						renderRightWindow = true;
						rightWindowIndex = craftList[i].index;
					}
			}

			if (renderRightWindow) {
				if (Collisions::collides(mousePos, 1, 1, craftButton_tr->getPos(), craftButton_tr->getW(), craftButton_tr->getH())) {
					//si hay acciones
					if (shelterScene->getActions() > 0) {
						bool isCraftable = craftSys->CraftItem(workshopItems[rightWindowIndex], craftButton_tr->getPos().getX() * 3 / 2, consts::WINDOW_HEIGHT / 3, this, false);

						if (isCraftable) {
							if (workshopItems[rightWindowIndex] == SPACESHIP_CABIN) {
								mngr_->getGame()->cabin = true;
								rocketTopImg->setAlpha(255);
							}
							else if (workshopItems[rightWindowIndex] == SPACESHIP_RADAR) {
								mngr_->getGame()->radar = true;
								rocketMidImg->setAlpha(255);
							}
							else if (workshopItems[rightWindowIndex] == SPACESHIP_ROCKETS) {
								mngr_->getGame()->rockets = true;
								rocketBotImg->setAlpha(255);
							}
							renderRightWindow = false;
							//gastar accion
							shelterScene->useAction();

							if (mngr_->getGame()->rockets && mngr_->getGame()->radar && mngr_->getGame()->cabin)
								endGame = true;
						}
					}
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

void SpaceshipStation::render() {
	falseMngr->refresh();
	if (renderFlag) {
		bg->render();
		bButton->render();

		rocketTop->render();
		rocketMid->render();
		rocketBot->render();

		for (int i = 0; i < workshopItems.size() && i < 4; ++i) {
			if ((workshopItems[i] == SPACESHIP_CABIN && !mngr_->getGame()->cabin) ||
				(workshopItems[i] == SPACESHIP_ROCKETS && !mngr_->getGame()->rockets)
				|| (workshopItems[i] == SPACESHIP_RADAR && !mngr_->getGame()->radar)) {

				craftList[i].index = listIndex + i;
				craftList[i].slot->render();

				rightWindowRender();
			}
		}
	}
	else if (loot != nullptr) {
		bButton->render();
	}
}

void SpaceshipStation::rightWindowRender() {
	if (renderRightWindow) {

		float offsetX = bg_tr->getPos().getX() + bg_tr->getW() * (3.0f / 4.0f);
		float offsetY = bg_tr->getPos().getY() + 35;

		std::string itemName = ITEMS_INFO[craftSys->getCrafts()->find(workshopItems[rightWindowIndex])->first].itemName;

		Texture* text = new Texture(sdlutils().renderer(), itemName, sdlutils().fonts().at("Orbitron32"), build_sdlcolor(0xffffffff));
		SDL_Rect dest{ offsetX - text->width() / 2  , offsetY ,text->width(),text->height() };
		text->render(dest, 0);

		offsetY += text->height() + 25;
		delete text;

		int imgRow = ITEMS_INFO[craftSys->getCrafts()->find(workshopItems[rightWindowIndex])->first].row;
		int imgCol = ITEMS_INFO[craftSys->getCrafts()->find(workshopItems[rightWindowIndex])->first].col;
		renderImg(offsetX - 32, offsetY, imgRow, imgCol);

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


			text = new Texture(sdlutils().renderer(), to_string(aux) + "/" + to_string(itemsNeeded[i].cantidad), sdlutils().fonts().at("Orbitron32"), build_sdlcolor(0xffffffff));
			dest = { (int)(offsetX + 30) , (int)offsetY + 48 - text->height() / 2 ,text->width(),text->height() };
			text->render(dest, 0);
			delete text;

			text = new Texture(sdlutils().renderer(), ITEMS_INFO[itemsNeeded[i].name].itemName, sdlutils().fonts().at("Orbitron32"), build_sdlcolor(0xffffffff));
			dest = { (int)(offsetX + 80) , (int)offsetY + 24 - text->height() / 2 ,text->width(),text->height() };
			text->render(dest, 0);
			delete text;

			offsetY += 48 + 20;

			craftButton->render();
			text = new Texture(sdlutils().renderer(), "CRAFT", sdlutils().fonts().at("Orbitron32"), build_sdlcolor(0xffffffff));
			dest = { (int)(craftButton_tr->getPos().getX() + craftButton_tr->getW() / 2 - text->width() / 2),
				(int)(craftButton_tr->getPos().getY() + craftButton_tr->getH() / 2 - text->height() / 2),text->width(),text->height() };
			text->render(dest, 0);
			delete text;
		}
	}
}