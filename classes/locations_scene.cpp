#include "locations_scene.h"
#include "../game/Game.h"
#include "../classes/raid_scene.h"
#include "../classes/location_button.h"
#include "../sdlutils/Texture.h"
#include "../components/Image.h"
#include "../sdlutils/SDLUtils.h"

LocationsScene::LocationsScene(Game* g) {
	 auto button = new LocationButton(Vector2D(100, 300), &sdlutils().images().at("shelterButton"), changeToRaid, g, mngr_);
	 mngr_->addEntity(button);
}

void LocationsScene::changeToRaid(Game* g, int index) {

	g->getStateMachine()->changeState(new RaidScene(paths[index]));
	g->getStateMachine()->currentState()->init();
}

void LocationsScene::render() {
	sdlutils().images().at("locations_image").render(build_sdlrect(0,0, sdlutils().width(), sdlutils().height()));
	GameScene::render();
}
