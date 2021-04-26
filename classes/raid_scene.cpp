#include "raid_scene.h"
#include "../game/Game.h"
#include "hud.h"
#include "../classes/pause_scene.h"
#include "../classes/camera.h"
#include "../sdlutils/InputHandler.h"
#include "../components/transitionComponent.h";
#include "../components/TextWithBackGround.h"

void RaidScene::init() {
	loadMap(path_);

	Player* player = static_cast<Player*>(mngr_->getHandler<Player_hdlr>());

	hud* h = new hud(mngr_, new Transform(Vector2D(100, 100), 64, 64, 0), player);


	int winWidth = consts::WINDOW_WIDTH;
	int winheight = consts::WINDOW_HEIGHT;
	float timeToFade = 2;
	Entity* e = mngr_->addEntity();
	e->addComponent<Transform>(Vector2D(), winWidth, winheight);
	e->addComponent<Image>(&sdlutils().images().at("black"), true);
	e->addComponent<TransitionComponent>(timeToFade);
	mngr_->addRenderLayer<Interface>(e);

	e = mngr_->addEntity();
	e->addComponent<Transform>(Vector2D(winWidth / 2, winheight / 2), winWidth, winheight);
	e->addComponent<TextWithBackground>(name,
		sdlutils().fonts().at("ARIAL32"), build_sdlcolor(0xffffffff), nullptr, false, 0, true);
	e->addComponent<TransitionComponent>(timeToFade);
	mngr_->addRenderLayer<Interface>(e);
}

void RaidScene::update() {
	GameScene::update();
	
	if (ih().keyDownEvent() && ih().isKeyDown(SDL_SCANCODE_ESCAPE)) {
		g_->getStateMachine()->pushState(new PauseScene(g_));
		g_->getStateMachine()->currentState()->init();
	}
}