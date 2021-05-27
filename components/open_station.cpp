#include "open_station.h"

Open_station::Open_station(Entity* st) {
	station = st; eClicked = false;
};
void Open_station::init() { myTr = entity_->getComponent<Transform>(); playerTr = entity_->getMngr()->getHandler<Player_hdlr>()->getComponent<Transform>();
}

void Open_station::update() {
	if (ih().isKeyDown(SDL_SCANCODE_E) && !eClicked && !playerTr->getEntity()->getComponent<InventoryController>()->isInvOpen()) {
		eClicked = true;
		if (Collisions::collides(myTr->getPos(), myTr->getW(), myTr->getH(), playerTr->getPos(), playerTr->getW(), playerTr->getW())) {
			Workshop* aux = dynamic_cast<Workshop*>(station);
			if (aux != nullptr) aux->setRenderFlag(true);
			else {
				static_cast<SleepStation*>(station)->setRenderFlag(true);
			}
		}
	}
	else if (eClicked && ih().isKeyUp(SDL_SCANCODE_E)) { eClicked = false;}
}