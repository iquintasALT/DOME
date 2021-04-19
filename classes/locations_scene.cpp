#include "locations_scene.h"
#include "../game/Game.h"
#include "../classes/raid_scene.h"
#include "../classes/location_button.h"
#include "../sdlutils/Texture.h"
#include "../components/Image.h"
#include "../sdlutils/SDLUtils.h"

LocationsScene::LocationsScene(Game* g) : GameScene(g) {
	button = new LocationButton(Vector2D(100, 300), &sdlutils().images().at("location_icon"), g, mngr_, buttonNumber++);
	mngr_->addEntity(button);
	shelter = new LocationButton(Vector2D(400, 300), &sdlutils().images().at("shelterButton"), g, mngr_, buttonNumber++);
	mngr_->addEntity(shelter);
}

void LocationsScene::changeToRaid(Game* g, int index) {
	g->getStateMachine()->changeState(new RaidScene(paths[index], g));
	g->getStateMachine()->currentState()->init();
}

void LocationsScene::render() {
	sdlutils().images().at("locations_image").render(build_sdlrect(0, 0, sdlutils().width(), sdlutils().height()));
	GameScene::render();
}

void LocationsScene::update() {
	Vector2D mousePos(ih().getMousePos().first, ih().getMousePos().second);
	if (ih().getMouseButtonState(InputHandler::LEFT) && !mouseClick) {
		mouseClick = true;

		if (Collisions::collides(mousePos, 1, 1, button->getComponent<Transform>()->getPos(), button->getComponent<Transform>()->getW(),
			button->getComponent<Transform>()->getH())) {
			changeToRaid(g_, 0);
		}
		else if (Collisions::collides(mousePos, 1, 1, shelter->getComponent<Transform>()->getPos(), shelter->getComponent<Transform>()->getW(),
			shelter->getComponent<Transform>()->getH())) {
			aux(g_);
		}
	}
	else if (!ih().getMouseButtonState(InputHandler::LEFT)) { mouseClick = false; }
}

void LocationsScene::aux(Game* g) {
	g->getStateMachine()->pushState(new ShelterScene(g));
	g->getStateMachine()->currentState()->init();
}