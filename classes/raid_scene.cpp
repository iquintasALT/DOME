#include "raid_scene.h"
#include "../game/Game.h"
#include "hud.h"
#include "../classes/pause_scene.h"
#include "../classes/camera.h"
#include "../sdlutils/InputHandler.h"
#include "../components/TextWithBackGround.h"

void RaidScene::init() {
	loadMap(path_);

	Player* player = static_cast<Player*>(mngr_->getHandler<Player_hdlr>());

	hud* h = new hud(mngr_, new Transform(Vector2D(100, 100), 64, 64, 0), player);
}

void RaidScene::update() {
	GameScene::update();
	
	if (ih().keyDownEvent() && ih().isKeyDown(SDL_SCANCODE_ESCAPE)) {
		g_->getStateMachine()->pushState(new PauseScene(g_));
		g_->getStateMachine()->currentState()->init();
	}
}