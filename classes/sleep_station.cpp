#include "sleep_station.h"
#include "../classes/locations_scene.h"
#include "../game/Game.h"
#include "../classes/physiognomy.h"
#include "../classes/player.h"
#include "../components/tiredness_component.h"
#include "../classes/shelter_scene.h"

SleepStation::SleepStation(Manager* realMngr_, Manager* mngr_, ShelterScene* shelterScene_) : Entity(realMngr_) {
	realMngr_->addEntity(this);
	realMngr_->addRenderLayer<Interface>(this);

	renderFlag = false;
	mouseClick = false;

	shelterScene = shelterScene_;
	playerTr = realMngr_->getHandler<Player_hdlr>()->getComponent<Transform>();

	falseMngr = mngr_;

	//INICIALIZACION IMAGENES DEL FONDO, FLECHAS Y X PARA SALIR
	bg = mngr_->addEntity();
	bButton = mngr_->addEntity();
	sleep0 = mngr_->addEntity();
	sleep1 = mngr_->addEntity();
	sleep2 = mngr_->addEntity();

	Vector2D bg_size = { 790.5, 535.5 };
	Vector2D bg_pos = Vector2D(sdlutils().width() / 2 - bg_size.getX() / 2, sdlutils().height() / 2 - bg_size.getY() / 2.5f);
	Vector2D bButton_size = { 65,64 };
	Vector2D bButton_pos = Vector2D(bg_pos.getX() - bButton_size.getX() / 2, bg_pos.getY() - bButton_size.getY() / 2);

	setImg(bg, bg_pos, bg_size, "station_bg");
	setImg(bButton, bButton_pos, bButton_size, "craft_back_button");

	bg_tr = bg->getComponent<Transform>();
	bButton_tr = bButton->getComponent<Transform>();

	text = new Texture(sdlutils().renderer(), "BED", sdlutils().fonts().at("OrbitronRegular"), build_sdlcolor(0xffffffff));
	text->width();
	dest_text = { (int) (bg_pos.getX() + bg_tr->getW() / 2 - text->width()),
		(int) (bg_pos.getY() + bg_tr->getH() * (0.5f / 4.0f) - text->height()),
		text->width()*2,text->height()*2};

	Vector2D sleepButton_size = { 256, 128 };
	Vector2D sleep_pos = { bg_pos.getX() + bg_tr->getW() / 2 - sleepButton_size.getX() / 2,
		bg_pos.getY() + bg_tr->getH() * (1.5f / 4.0f) - sleepButton_size.getY() / 1.5f };
	setImg(sleep0, sleep_pos, sleepButton_size, "0_hour_sleep");
	sleep0_tr = sleep0->getComponent<Transform>();

	Vector2D sleep_pos1 = { bg_pos.getX() + bg_tr->getW() / 2 - sleepButton_size.getX() / 2,
		bg_pos.getY() + bg_tr->getH() * (2.5f / 4.0f) - sleepButton_size.getY() / 1.5f };
	setImg(sleep1, sleep_pos1, sleepButton_size, "1_hour_sleep");
	sleep1_tr = sleep1->getComponent<Transform>();

	Vector2D sleep_pos2 = { bg_pos.getX() + bg_tr->getW() / 2 - sleepButton_size.getX() / 2,
		bg_pos.getY() + bg_tr->getH() * (3.5f / 4.0f) - sleepButton_size.getY() / 1.5f };
	setImg(sleep2, sleep_pos2, sleepButton_size, "2_hour_sleep");
	sleep2_tr = sleep2->getComponent<Transform>();
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
	falseMngr->refresh();

	if (renderFlag) {
		Vector2D mousePos(ih().getMousePos().first, ih().getMousePos().second);
		if (ih().getMouseButtonState(InputHandler::LEFT) && !mouseClick) {
			mouseClick = true;

			if (Collisions::collides(mousePos, 1, 1, bButton_tr->getPos(), bButton_tr->getW(), bButton_tr->getH())) {
				renderFlag = false;
				playerTr->getEntity()->setActive(true);
			}
			else if (Collisions::collides(mousePos, 1, 1, sleep0_tr->getPos(), sleep0_tr->getW(), sleep0_tr->getH())) {
				renderFlag = false;
				playerTr->getEntity()->setActive(true);
				goToSleep(0, 0);
			}
			else if (Collisions::collides(mousePos, 1, 1, sleep2_tr->getPos(), sleep2_tr->getW(), sleep2_tr->getH())) {
				renderFlag = false;
				playerTr->getEntity()->setActive(true);
				if (shelterScene->getActions() >= 2) {
					goToSleep(8, 2);
				}
			}
			else if (Collisions::collides(mousePos, 1, 1, sleep1_tr->getPos(), sleep1_tr->getW(), sleep1_tr->getH())) {
				renderFlag = false;
				playerTr->getEntity()->setActive(true);
				if (shelterScene->getActions() >= 1) {
					goToSleep(3, 1);
				}
			}
		}
	}
	else if (!ih().getMouseButtonState(InputHandler::LEFT)) { mouseClick = false; }
}

void SleepStation::goToSleep(int hours, int numberOfActions)
{
	int nDays = mngr_->getGame()->numDays++;
	if(nDays > consts::MAX_DAYS)
		mngr_->ChangeScene(new LoseScene(mngr_->getGame(), WAYSTODIE::DAYS), SceneManager::SceneMode::ADDITIVE);

	mngr_->getHandler<Player_hdlr>()->getComponent<TirednessComponent>()->sleep(hours);
	for(int i = 0; i < numberOfActions; i++) shelterScene->useAction();
	shelterScene->sleepTransition();
}

void SleepStation::render() {
	falseMngr->refresh();
	if (renderFlag) {
		bg->render();
		bButton->render();

		text->render(dest_text);
		sleep0->render();
		sleep1->render();
		sleep2->render();
	}
}

void SleepStation::renderImg(float posX, float posY, int row, int col, int sizeX, int sizeY) {
	Entity* aux = getMngr()->addEntity();
	aux->addComponent<Transform>(Vector2D{ posX,posY }, sizeX, sizeY, 0);
	aux->addComponent<Image>(&sdlutils().images().at("items"), 4, 3, row, col, true)->render();
	aux->setActive(false);
}
