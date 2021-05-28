#include "open_station.h"

OpenStation::OpenStation(Entity* st) {
	station = st; eClicked = false;
};
void OpenStation::init() { myTr = entity_->getComponent<Transform>(); playerTr = entity_->getMngr()->getHandler<Player_hdlr>()->getComponent<Transform>();
}

void OpenStation::update() {
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