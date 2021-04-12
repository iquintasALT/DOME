#include "locations_scene.h"
#include "../game/Game.h"
#include "../classes/raid_scene.h"
#include "../classes/menu_button.h"
#include "../sdlutils/Texture.h"
#include "../components/Image.h"
#include "../sdlutils/SDLUtils.h"

LocationsScene::LocationsScene(Game* g):GameScene(g) {
	mngr_->addEntity(new MenuButton(Vector2D(100, 300),
		&sdlutils().images().at("shelterButton"), changeToRaid, g, mngr_));

	mngr_->addEntity(new MenuButton(Vector2D(500, 100),
		&sdlutils().images().at("raidButton"), changeToRaid2, g, mngr_));

}

void LocationsScene::changeToRaid2(Game* g) {
	g->getStateMachine()->changeState(new RaidScene("./resources/tilemap/template.tmx", g));
	g->getStateMachine()->currentState()->init();
}
void LocationsScene::changeToRaid(Game* g) {
	g->getStateMachine()->changeState(new RaidScene("./resources/tilemap/template.tmx", g));
	g->getStateMachine()->currentState()->init();
}

void LocationsScene::render() {
	sdlutils().images().at("locations_image").render(build_sdlrect(0,0, sdlutils().width(), sdlutils().height()));
	GameScene::render();
}
