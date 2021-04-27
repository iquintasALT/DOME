#include "open_station.h"

Open_station::Open_station(Entity* st) {
	station = st; eClicked = false;
};
void Open_station::init() {
	myTr = entity_->getComponent<Transform>(); playerTr = entity_->getMngr()->getHandler<Player_hdlr>()->getComponent<Transform>();
}

void Open_station::update() {
	if (ih().isKeyDown(SDL_SCANCODE_E) && !eClicked) {
		eClicked = true;
		if (Collisions::collides(myTr->getPos(), myTr->getW(), myTr->getH(), playerTr->getPos(), playerTr->getW(), playerTr->getW())) {
			Workshop* aux = dynamic_cast<Workshop*>(station);
			if (aux != nullptr && !aux->isRendering()) aux->setRenderFlag(true);
			else {
				SleepStation* aux2 = dynamic_cast<SleepStation*>(station);
				if (aux2 != nullptr && !aux2->isRendering())
					aux2->setRenderFlag(true);
			}
		}
	}
	else if (!ih().isKeyUp(SDL_SCANCODE_E) && eClicked) eClicked = false;
}